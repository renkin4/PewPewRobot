// YangIsAwesome

#include "PlayerController_Base.h"
#include "Character_Base.h"
#include "MyGameMode_Base.h"
#include "PlayerState_Base.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"



APlayerController_Base::APlayerController_Base(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
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

AActor * APlayerController_Base::SpawnProjectile(FVector SpawnLoc, FRotator SpawnRot, TSubclassOf<AActor> ProjectileToSpawn, AActor* ProjOwner)
{
	if (Role < ROLE_Authority)
	{
		SERVER_SpawnProjectile(SpawnLoc, SpawnRot, ProjectileToSpawn, ProjOwner);
		return nullptr;
	}

	FTransform SpawnTM(SpawnRot, SpawnLoc);
	AActor* Projectile = Cast<AActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, ProjectileToSpawn, SpawnTM));

	if (Projectile)
	{
		Projectile->Instigator = Instigator;
		Projectile->SetOwner(ProjOwner);

		UGameplayStatics::FinishSpawningActor(Projectile, SpawnTM);
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
			SpringArmComp[0]->TargetArmLength * SpringAimLengthModifier,
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

void APlayerController_Base::SERVER_SpawnProjectile_Implementation(FVector SpawnLoc, FRotator SpawnRot, TSubclassOf<AActor> ProjectileToSpawn, AActor* ProjOwner)
{
	SpawnProjectile(SpawnLoc, SpawnRot, ProjectileToSpawn, ProjOwner);
}

bool APlayerController_Base::SERVER_SpawnProjectile_Validate(FVector SpawnLoc, FRotator SpawnRot, TSubclassOf<AActor> ProjectileToSpawn, AActor* ProjOwner)
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
