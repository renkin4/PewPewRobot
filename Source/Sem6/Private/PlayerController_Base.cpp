// YangIsAwesome

#include "PlayerController_Base.h"
#include "Character_Base.h"
#include "MyGameMode_Base.h"
#include "MyGameState_Base.h"
#include "PlayerState_Base.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "MyCheatManager_Base.h"
#include "Projectile_Base.h"



APlayerController_Base::APlayerController_Base(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	bIsAiming = false;
	SpringAimLengthModifier = 1.0f;
	/*Setup Timeline*/
	AimTimeline = ObjectInitializer.CreateDefaultSubobject<UTimelineComponent>(this, TEXT("AimingTimeline"));

	//Bind the Callbackfuntion for the float return value
	InterpFunction.BindUFunction(this, FName{ TEXT("AimTimelineFloatReturn") });
	OnAimTimelineFinishEvent.BindDynamic(this, &APlayerController_Base::AimOnTimelineFinish);
	/*---------------------------------------------*/
}

void APlayerController_Base::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Aim", IE_Pressed, this, &APlayerController_Base::OnAim);
	InputComponent->BindAction("Aim", IE_Released, this, &APlayerController_Base::OnReleasedAim);
}

void APlayerController_Base::ProcessPlayerInput(const float DeltaTime, const bool bGamePaused)
{
	Super::ProcessPlayerInput(DeltaTime, bGamePaused);

	if (MyCharacter != GetPawn())
	{
		MyCharacter = Cast<ACharacter>(GetPawn()) ? Cast<ACharacter>(GetPawn()) : NULL;
		CLIENT_PawnChanged();
	}

}

void APlayerController_Base::Possess(APawn * InPawn)
{
	EnableCheats();
	Super::Possess(InPawn);
	OnPossessEvent(InPawn);
	ACharacter_Base* MyChar = Cast<ACharacter_Base>(InPawn);
	if (MyChar) 
	{
		InitializeVarOnPossessed(MyChar, this, Cast<APlayerState_Base>(GetPlayerState()));
	}
}

void APlayerController_Base::OnPossessEvent_Implementation(APawn * InPawn)
{
}

void APlayerController_Base::InitializeVarOnPossessed(ACharacter* MyChar, APlayerController_Base * SelfPController, APlayerState_Base * SelfPlayerState)
{
	if (Role < ROLE_Authority) 
	{
		SERVER_InitializeVarOnPossessed(MyChar, SelfPController, SelfPlayerState);
		return;
	}
	ACharacter_Base* CharRef = Cast<ACharacter_Base>(MyChar);
	CharRef->SetMyPlayerController(SelfPController);
	CharRef->SetMyPlayerState(SelfPlayerState);
	CharRef->OnRep_MyPlayerState();
}

APlayerState* APlayerController_Base::GetPlayerState()
{
	return PlayerState;
}

void APlayerController_Base::RespawnPlayer()
{
	AMyGameMode_Base* GM = Cast<AMyGameMode_Base>(GetWorld()->GetAuthGameMode());
	if (Role < ROLE_Authority) 
	{
		SERVER_RespawnPlayer();
	}
	if (GM) 
	{
		GM->RespawnPlayer(this);
	}
}

AActor * APlayerController_Base::SpawnProjectile(FVector SpawnLoc, FRotator SpawnRot, TSubclassOf<AActor> ProjectileToSpawn, AActor* ProjOwner, AActor* HomingTarget)
{
	if (Role < ROLE_Authority)
	{
		SERVER_SpawnProjectile(SpawnLoc, SpawnRot, ProjectileToSpawn, ProjOwner, HomingTarget);
		return nullptr;
	}

	FTransform SpawnTM(SpawnRot, SpawnLoc);
	AActor* Projectile = Cast<AActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, ProjectileToSpawn, SpawnTM));

	if (Projectile)
	{
		Projectile->Instigator = Instigator;
		Projectile->SetOwner(ProjOwner);
		UGameplayStatics::FinishSpawningActor(Projectile, SpawnTM);
		AProjectile_Base* HomingProjectile = Cast<AProjectile_Base>(Projectile);
		if (HomingProjectile)
			HomingProjectile->SetHommingMissle(HomingTarget);
	}

	return Projectile;
}

void APlayerController_Base::BeginPlay()
{
	Super::BeginPlay();
	//Add the float curve to the timeline and connect it to your timelines's interpolation function
	AimTimeline->AddInterpFloat(AimingFloatCurve, InterpFunction, FName{ TEXT("Floaty") });
	AimTimeline->SetTimelineFinishedFunc(OnAimTimelineFinishEvent);

}

void APlayerController_Base::SERVER_InitializeVarOnPossessed_Implementation(ACharacter* MyChar, APlayerController_Base * SelfPController, APlayerState_Base * SelfPlayerState)
{
	InitializeVarOnPossessed(MyChar,SelfPController, SelfPlayerState);
}

bool APlayerController_Base::SERVER_InitializeVarOnPossessed_Validate(ACharacter* MyChar, APlayerController_Base * SelfPController, APlayerState_Base * SelfPlayerState)
{
	return true;
}

void APlayerController_Base::OnAim()
{
	AimTimeline->Play();
	SetIsAiming(true);
	SetCharacterControlledYaw(GetIsAiming());
}

void APlayerController_Base::OnReleasedAim()
{
	AimTimeline->Reverse();
	SetIsAiming(false);
	SetCharacterControlledYaw(GetIsAiming());
}

bool APlayerController_Base::GetIsAiming()
{
	return bIsAiming;
}

bool APlayerController_Base::SetIsAiming(bool bShouldAim)
{
	bIsAiming = bShouldAim;
	return bIsAiming;
}

void APlayerController_Base::AimTimelineFloatReturn(float val)
{
	//TODO set these Variable Outsite On Possessed
	//Zooming
	if(MyCharacter->IsValidLowLevel()) 
	{
		MyCharacter->GetComponents<USpringArmComponent>(SpringArmComp);
		MyCharacter->GetComponents<UChildActorComponent>(ZoomLocation);

		SpringArmComp[0]->TargetArmLength = FMath::Lerp(
			SpringArmDefaultRelativeArmLength,
			0.0f,
			val);

		SpringArmComp[0]->SetRelativeLocation(FMath::Lerp(
			SpringArmDefaultRelativeLocation,
			ZoomLocation[0]->RelativeLocation,
			val));
	}
	else 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CRITICAL ERROR: Character Ref Missing On PlayerController"));
	}
	
	/*----------------------------*/

}

void APlayerController_Base::AimOnTimelineFinish()
{

}

void APlayerController_Base::SetCharacterControlledYaw(bool bIsFollow)
{
	//Multicast this
	if (Role < ROLE_Authority) 
	{
		SERVER_SetCharacterControlledYaw(bIsFollow, MyCharacter);
	}
	else 
	{
		CLIENT_SetCharacterControlledYaw(bIsFollow);
	}

}

void APlayerController_Base::OnLeaveTeam(uint8 TeamNum)
{
	if (Role < ROLE_Authority) 
	{
		SERVER_OnLeaveTeam(TeamNum);
		return;
	}
	UWorld* World = GetWorld();
	AMyGameState_Base* GS = Cast<AMyGameState_Base>(World->GetGameState());
	if (GS) 
	{
		GS->OnLeaveTeam(TeamNum);
	}
}

void APlayerController_Base::SetReady(bool bShouldReady)
{
	if (Role < ROLE_Authority)
	{
		SERVER_SetReady(bShouldReady);
		return;
	}
	APlayerState_Base* PState = Cast<APlayerState_Base>(GetPlayerState());
	if (PState) 
	{
		PState->SetPlayerReady(bShouldReady);
	}
}

void APlayerController_Base::SetActorOwner(AActor * ActorToSet, AActor * ActorOwner)
{
	if (ActorToSet->IsValidLowLevel())
		ActorToSet->SetOwner(ActorOwner);
	else
		return;
	if (Role < ROLE_Authority) 
	{
		SERVER_SetActorOwner(ActorToSet, ActorOwner);
	}
}

void APlayerController_Base::SERVER_SetActorOwner_Implementation(AActor * ActorToSet, AActor * ActorOwner)
{
	SetActorOwner(ActorToSet, ActorOwner);
}

bool APlayerController_Base::SERVER_SetActorOwner_Validate(AActor * ActorToSet, AActor * ActorOwner)
{
	return true;
}

void APlayerController_Base::SERVER_SetReady_Implementation(bool bShouldReady)
{
	SetReady(bShouldReady);
}

bool APlayerController_Base::SERVER_SetReady_Validate(bool bShouldReady)
{
	return true;
}

void APlayerController_Base::SERVER_OnLeaveTeam_Implementation(uint8 TeamNum)
{
	OnLeaveTeam(TeamNum);
}

bool APlayerController_Base::SERVER_OnLeaveTeam_Validate(uint8 TeamNum)
{
	return true;
}

void APlayerController_Base::DelayOnUpdateSelectionUI()
{
	UWorld* World = GetWorld();
	AMyGameState_Base* GS = Cast<AMyGameState_Base>(World->GetGameState());
	TArray<APlayerState*> PS;
	APlayerState_Base* PStateBase;
	if (GS)
	{
		PS = GS->PlayerArray;
		for (APlayerState* PState : PS) 
		{
			PStateBase = Cast<APlayerState_Base>(PState);
			/*Updating UI Selection by passing same team num*/
			GS->OnJoinTeam(PStateBase, PStateBase->GetTeamNum());
		}
	}
}

void APlayerController_Base::SetMyCurrency(float Amount)
{
	if (Role < ROLE_Authority) 
	{
		SERVER_SetMyCurrency(Amount);
		return;
	}
	UMyCheatManager_Base* MyCheatManager = Cast<UMyCheatManager_Base>(CheatManager);
	if (MyCheatManager)
	{
		MyCheatManager->SetMyCurrency(Amount);
	}
}

void APlayerController_Base::MaxStamina()
{
	if (Role < ROLE_Authority)
	{
		SERVER_MaxStamina();
		return;
	}
	UMyCheatManager_Base* MyCheatManager = Cast<UMyCheatManager_Base>(CheatManager);
	if (MyCheatManager)
	{
		MyCheatManager->MaxStamina();
	}
}

void APlayerController_Base::YangIsAwesome()
{
	if (Role < ROLE_Authority)
	{
		SERVER_YangIsAwesome();
		return;
	}
	UMyCheatManager_Base* MyCheatManager = Cast<UMyCheatManager_Base>(CheatManager);
	if (MyCheatManager)
	{
		MyCheatManager->God();
	}
}

void APlayerController_Base::SERVER_MaxStamina_Implementation()
{
	MaxStamina();
}

bool APlayerController_Base::SERVER_MaxStamina_Validate()
{
	return true;
}

void APlayerController_Base::SERVER_SetMyCurrency_Implementation(float Amount)
{
	SetMyCurrency(Amount);
}

bool APlayerController_Base::SERVER_SetMyCurrency_Validate(float Amount)
{
	return true;
}

void APlayerController_Base::SERVER_YangIsAwesome_Implementation()
{
	YangIsAwesome();
}

bool APlayerController_Base::SERVER_YangIsAwesome_Validate()
{
	return true;
}

void APlayerController_Base::SERVER_UpdateSelectionUI_Implementation()
{
	UpdateSelectionUI();
}

bool APlayerController_Base::SERVER_UpdateSelectionUI_Validate()
{
	return true;
}

void APlayerController_Base::UpdateSelectionUI()
{
	if (Role < ROLE_Authority) 
	{
		SERVER_UpdateSelectionUI();
		return;
	}
	GetWorldTimerManager().SetTimer(DelayOnUpdateSelectionUIHandle, this, &APlayerController_Base::DelayOnUpdateSelectionUI, 0.5f, false);
}

void APlayerController_Base::UpdateReadyStatus()
{
	if (Role < ROLE_Authority)
	{
		SERVER_UpdateReadyStatus();
		return;
	}
	UWorld* World = GetWorld();
	AMyGameState_Base* GS = Cast<AMyGameState_Base>(World->GetGameState());
	APlayerState_Base* PS = Cast<APlayerState_Base>(GetPlayerState());
	if (GS && PS)
	{
		GS->UpdateReadyStatus(PS);
	}
}

void APlayerController_Base::OnJoinTeam(uint8 TeamNum)
{
	if (Role < ROLE_Authority) 
	{
		SERVER_OnJoinTeam(TeamNum);
		return;
	}
	UWorld* World = GetWorld();
	AMyGameState_Base* GS = Cast<AMyGameState_Base>(World->GetGameState());
	APlayerState_Base* PStateBase = Cast<APlayerState_Base>(GetPlayerState());
	if (GS && PStateBase)
	{
		GS->OnJoinTeam(PStateBase, TeamNum);
	}
}

void APlayerController_Base::SERVER_OnJoinTeam_Implementation(uint8 TeamNum)
{
	OnJoinTeam(TeamNum);
}

bool APlayerController_Base::SERVER_OnJoinTeam_Validate(uint8 TeamNum)
{
	return true;
}

void APlayerController_Base::SERVER_UpdateReadyStatus_Implementation()
{
	UpdateReadyStatus();
}

bool APlayerController_Base::SERVER_UpdateReadyStatus_Validate()
{
	return true;
}

void APlayerController_Base::SERVER_SpawnProjectile_Implementation(FVector SpawnLoc, FRotator SpawnRot, TSubclassOf<AActor> ProjectileToSpawn, AActor* ProjOwner, AActor* HomingTarget)
{
	SpawnProjectile(SpawnLoc, SpawnRot, ProjectileToSpawn, ProjOwner, HomingTarget);
}

bool APlayerController_Base::SERVER_SpawnProjectile_Validate(FVector SpawnLoc, FRotator SpawnRot, TSubclassOf<AActor> ProjectileToSpawn, AActor* ProjOwner, AActor* HomingTarget)
{
	return true;
}


void APlayerController_Base::SERVER_RespawnPlayer_Implementation()
{
	RespawnPlayer();
}

bool APlayerController_Base::SERVER_RespawnPlayer_Validate()
{
	return true;
}

void APlayerController_Base::CLIENT_SetCharacterControlledYaw_Implementation(bool bIsFollow)
{
	if (MyCharacter->IsValidLowLevel())
	{
		MyCharacter->bUseControllerRotationYaw = bIsFollow;
		MyCharacter->GetCharacterMovement()->bOrientRotationToMovement = !bIsFollow;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CRITICAL ERROR: Character Ref Missing On PlayerController"));
	}
}

void APlayerController_Base::SERVER_SetCharacterControlledYaw_Implementation(bool bIsFollow, ACharacter* CharacterOwner)
{
	SetCharacterControlledYaw(bIsFollow);
	/*Setting it on ServerSide Harcoded*/
	if (CharacterOwner->IsValidLowLevel())
	{
		CharacterOwner->bUseControllerRotationYaw = bIsFollow;
		CharacterOwner->GetCharacterMovement()->bOrientRotationToMovement = !bIsFollow;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CRITICAL ERROR: Character Ref Missing On PlayerController"));
	}
	/*----------------------*/
}

bool APlayerController_Base::SERVER_SetCharacterControlledYaw_Validate(bool bIsFollow, ACharacter* CharacterOwner)
{
	return true;
}

void APlayerController_Base::CLIENT_PawnChanged_Implementation()
{
	MyCharacter->GetComponents<USpringArmComponent>(SpringArmComp);
	SpringArmDefaultRelativeArmLength = SpringArmComp[0]->TargetArmLength;
	SpringArmDefaultRelativeLocation = SpringArmComp[0]->GetRelativeTransform().GetLocation();
}
