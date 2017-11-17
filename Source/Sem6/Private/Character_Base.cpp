// YangIsAwesome

#include "Character_Base.h"
#include "MyCharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "MyBlueprintFunctionLibrary.h"
#include "MyAIController.h"
#include "Net/UnrealNetwork.h"
#include "MyBox.h"
#include "Loot_Base.h"
#include "MyGameState_Base.h"
#include "PlayerState_Base.h"
#include "PlayerController_Base.h"
#include "Weapon_Base.h"
#include "DamageType_Base.h"
#include "SpawnPoint_Base.h"
#include "HighlightInterface.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavigationPath.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavigationSystem.h"
#include "MyPlayerStart_Base.h"
#include "Particles/ParticleSystemComponent.h"
#include "CharacterAnimInstance.h"
#include "Sem6.h"

// Sets default values
//Constructor
ACharacter_Base::ACharacter_Base(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UMyCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	bAlwaysRelevant = true;
	RunningSpeedModifier = 1.8f;
	WalkSpeedModifier = 1.0f;
	bIsRunning = false;
	CharacterState = ECharacterState::CS_Walk;
	Inventory.bIsWeaponExist = false;
	bBindDynamicDoOnce = true;
	bOnCollectDoOnce = true;
	MaxHealth = 100.0f;
	bDie = false;
	bIsDying = false;
	bIsHoldingBox = false;
	bIsAtBoxHolderLocation = false;
	SelectedItemIndex = 0;
	MaxStamina = 100.0f;
	Stamina = MaxStamina;
	bShouldRegenStamina = false;
	bIsPunching = false;
	CurrentWeaponIndex = 0;
	MaxNumOfWeapon = 6;
	bDropWeapon = false;
	bCheckMap = false;

	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	HomingLaucnherTarget = CreateDefaultSubobject<USceneComponent>(TEXT("Homing Launcher Target"));
	HomingLaucnherTarget->SetupAttachment(RootComponent);
}

void ACharacter_Base::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(ACharacter_Base, bIsRunning, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(ACharacter_Base, MyPlayerState, COND_None);
	DOREPLIFETIME_CONDITION(ACharacter_Base, bIsAtBoxHolderLocation, COND_None);
	DOREPLIFETIME_CONDITION(ACharacter_Base, MyPlayerController, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(ACharacter_Base, MaxHealth, COND_None);
	DOREPLIFETIME_CONDITION(ACharacter_Base, bIsTargeting, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(ACharacter_Base, Health, COND_None);
	DOREPLIFETIME_CONDITION(ACharacter_Base, Inventory, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(ACharacter_Base, Stamina, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(ACharacter_Base, bStaminaCheatEnabled, COND_OwnerOnly);
}

float ACharacter_Base::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float ActualDamage;
	//IgnoreOnDeath
	if (bIsDying||!bCanBeDamaged)
	{
		Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
		return 0.0f;
	}
	//---------------------------------//

	/*Taking damage*/
	UDamageType_Base* DamageTypeB = Cast<UDamageType_Base>(DamageEvent.DamageTypeClass->GetDefaultObject());
	IProcessDamageInterface* ProcessInterface = Cast<IProcessDamageInterface>(DamageTypeB);
	if (ProcessInterface) 
	{
		ActualDamage = ProcessInterface->Execute_ProcessDamageTypeDamage(DamageTypeB, Damage, this);
	}
	else 
	{
		ActualDamage = Damage;
	}
	Health = Health - ActualDamage;
	//---------------------------------//

	/*Run for server On Rep*/
	if (Role == ROLE_Authority)
		OnRep_Health();
	//---------------------------------//

	//DeathNotify
	if (Health <= 0.0f) 
	{
		OnDeathNotify();
	}
	//---------------------------------//

	//TODO Disable Running
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	return Damage;
}

ELootAbleType ACharacter_Base::GetLootableType_Implementation()
{
	return ELootAbleType::LAT_None;
}

EWeaponType ACharacter_Base::GetWeaponType_Implementation()
{
	return EWeaponType::WT_None;
}

float ACharacter_Base::ProcessDamageTypeDamage_Implementation(float Damage, AActor* ActorToIgnore)
{
	return 0.0f;
}

void ACharacter_Base::UpdateAnimInstanceData()
{
	UCharacterAnimInstance* CharAnimInst = Cast<UCharacterAnimInstance>(GetMesh()->GetAnimInstance());

	if (!CharAnimInst)
		return;

	// if player dead exit early
	if (!IsAlive())
	{
		CharAnimInst->IsAlive = false;
		CharAnimInst->IsMoving = false;
		CharAnimInst->IsRunning = false;
		CharAnimInst->IsFalling = false;
		return;
	}

	CharAnimInst->IsAlive = IsAlive();
	CharAnimInst->IsMoving = GetVelocity().Size() > 100.0f;
	CharAnimInst->IsRunning = IsRunning();
	CharAnimInst->IsFalling = GetMovementComponent()->IsFalling();
}

// Called when the game starts or when spawned
void ACharacter_Base::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	LocalHealth = Health;
	//I kinda Broke it, Server always Return 0.5f so i manually set it here
	CustomTimeDilation = 1.0f;

}

// Called every frame
void ACharacter_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateAnimInstanceData();

	if (MyPlayerController!=NULL  && GetController()->IsLocalController())
	{
		if(!bIsTargeting)
			SphereTraceLootable();

		SetTargetting(GetMyPlayerController()->GetIsAiming());
		RegenStamina();
	}

	if (GetIsTargetting() && GetCurrentWeapon()!= NULL)
	{
		if (GetCurrentWeapon()->GetWeaponFireType() == EWeaponFireType::WT_ProjecTile && !GetCurrentWeapon()->bIsHomming)
			GetCurrentWeapon()->DrawTrajectory();
		else if (GetCurrentWeapon()->bIsHomming) 
			GetCurrentWeapon()->HommingMissleTargetTrace();
	}
	
	if (bCheckMap) 
	{
		StartLocationPathParticleControl();
	}
}

// Called to bind functionality to input
void ACharacter_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	/*Bind Delegate input to functions*/
	if (PlayerInputComponent->IsValidLowLevel())
	{
		//WeaponChoice
		PlayerInputComponent->BindAxis("Forward", this, &ACharacter_Base::MoveForward);
		PlayerInputComponent->BindAxis("Right", this, &ACharacter_Base::MoveRight);
		PlayerInputComponent->BindAxis("LookUp", this, &ACharacter_Base::PitchLookUp);
		PlayerInputComponent->BindAxis("Turn", this, &ACharacter_Base::YawTurn);
		PlayerInputComponent->BindAxis("WeaponChoice", this, &ACharacter_Base::WeaponChoice);

		PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter_Base::OnJump);
		PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ACharacter_Base::OnFire);
		PlayerInputComponent->BindAction("Fire", IE_Released, this, &ACharacter_Base::OnReleaseFire);
		PlayerInputComponent->BindAction("Collect", IE_Pressed, this, &ACharacter_Base::OnCollect);
		PlayerInputComponent->BindAction("Collect", IE_Released, this, &ACharacter_Base::OnCollectRelease);
		PlayerInputComponent->BindAction("Score", IE_Pressed, this, &ACharacter_Base::OnScore);
		PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ACharacter_Base::OnAim);
		PlayerInputComponent->BindAction("Aim", IE_Released, this, &ACharacter_Base::OnReleasedAim);
		PlayerInputComponent->BindAction("SpeedRun", IE_Pressed, this, &ACharacter_Base::OnRun);
		PlayerInputComponent->BindAction("CheckMap", IE_Pressed, this, &ACharacter_Base::OnCheckMap);
		PlayerInputComponent->BindAction("CheckMap", IE_Released, this, &ACharacter_Base::OnReleaseCheckMap);
		PlayerInputComponent->BindAction("SpeedRun", IE_Released, this, &ACharacter_Base::OnWalk);
		PlayerInputComponent->BindAction("UseLootable", IE_Pressed, this, &ACharacter_Base::OnUseLootable);
		PlayerInputComponent->BindAction("SwitchSelection", IE_Pressed, this, &ACharacter_Base::OnSwitchSelection);
		PlayerInputComponent->BindAction("DropWeapon", IE_Pressed, this, &ACharacter_Base::OnDropWeapon);
		PlayerInputComponent->BindAction("DropWeapon", IE_Released, this, &ACharacter_Base::OnDropWeaponRelease);

	}
}

void ACharacter_Base::PossessedBy(AController * NewController)
{
	Super::PossessedBy(NewController);
}

void ACharacter_Base::MoveForward(float axis)
{
	FVector ControllerFwd = UKismetMathLibrary::GetForwardVector(GetControlRotation());
	AddMovementInput(ControllerFwd, axis);
}

void ACharacter_Base::MoveRight(float axis)
{
	FVector ControllerRight = UKismetMathLibrary::GetRightVector(GetControlRotation());
	AddMovementInput(ControllerRight, axis);
}

void ACharacter_Base::PitchLookUp(float axis)
{
	AddControllerPitchInput(axis);
}

void ACharacter_Base::YawTurn(float axis)
{
	AddControllerYawInput(axis);
}

void ACharacter_Base::StunPlayer(float StunDuration)
{
	if (MyPlayerController->IsValidLowLevel()) 
	{
		print("Stun");
		DisableInput(MyPlayerController);
		GetWorldTimerManager().SetTimer(RemoveStunHandler, this, &ACharacter_Base::RemovePlayerStun, StunDuration, false);
	}
}

void ACharacter_Base::RemovePlayerStun()
{
	if (MyPlayerController->IsValidLowLevel())
		EnableInput(MyPlayerController);
}

void ACharacter_Base::WeaponChoice(float axis)
{
	if (axis > 0.2f) 
	{
		uint8 SelectionChoice = (uint8)axis - 1;
		CurrentWeaponIndex = SelectionChoice;
		OnChangeWeapon();
	}
}

void ACharacter_Base::OnJump()
{
	Jump();
	return;
}

void ACharacter_Base::OnAim()
{
	CharacterState = ECharacterState::CS_Targetting;
}

void ACharacter_Base::OnReleasedAim()
{
	CharacterState = ECharacterState::CS_Walk;
}

void ACharacter_Base::OnUseLootable()
{
	UseLootable();
}

void ACharacter_Base::OnSwitchSelection()
{
	SelectedItemIndex++;
}

void ACharacter_Base::OnDropWeapon()
{
	bDropWeapon = true;

	AWeapon_Base* Weapon;
	TArray<UStaticMeshComponent*> StaticMeshComponents;
	Weapon = GetCurrentWeapon();
	if (Weapon == NULL)
		return;

	DetachActorFromMesh(Weapon);
	Weapon->GetComponents<UStaticMeshComponent>(StaticMeshComponents);
	SetLootableCollision(StaticMeshComponents[0], ECC_GameTraceChannel4, ECR_Block);

	Inventory.Weapon.Remove(Weapon->GetClass());
	WeaponArray.Remove(Weapon);

	OnChangeWeapon();
	UpdateInventoryUIDelegate.Broadcast();
}

void ACharacter_Base::OnDropWeaponRelease()
{
	bDropWeapon = false;
}

void ACharacter_Base::OnCheckMap()
{
	bCheckMap = true;
}

void ACharacter_Base::OnReleaseCheckMap()
{
	bCheckMap = false;
}

void ACharacter_Base::OnDrawStartLocationPath()
{
	const FVector ParticleOffSet = FVector(0.0f, 0.0f, 40.0f);
	UParticleSystemComponent* PathSegmentParticle;
	APlayerState_Base* PState = Cast<APlayerState_Base>(GetMyPlayerController()->PlayerState);
	if (PState)
	{
		UNavigationPath *tpath;
		UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(GetWorld());

		tpath = NavSys->FindPathToLocationSynchronously(GetWorld(), GetActorLocation(), PState->GetPlayerStartLocation()->GetActorLocation());

		if (tpath != NULL)
		{
			for (int pointiter = 0; pointiter < tpath->PathPoints.Num() - 1; pointiter++)
			{
				PathSegmentParticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CheckMapBeamParticle, tpath->PathPoints[pointiter] + ParticleOffSet, FRotator(0.0f, 0.0f, 0.0f), false);
				if (PathSegmentParticle)
				{
					PathSegmentParticle->SetBeamSourcePoint(0, tpath->PathPoints[pointiter] + ParticleOffSet, 0);
					PathSegmentParticle->SetBeamTargetPoint(0, tpath->PathPoints[pointiter + 1] + ParticleOffSet, 0);
					StartLocationPathParticles.Add(PathSegmentParticle);
				}
			}
		}
	}
}

void ACharacter_Base::FlushStartLocationParticles()
{
	for (auto PathParticles : StartLocationPathParticles) 
	{
		PathParticles->DestroyComponent();
	}
	StartLocationPathParticles.Empty();
}

void ACharacter_Base::StartLocationPathParticleControl()
{
	if (StartLocationPathParticles.Num() > 0)
		FlushStartLocationParticles();

	OnDrawStartLocationPath();

	GetWorldTimerManager().SetTimer(ResetPathParticle, this, &ACharacter_Base::FlushStartLocationParticles, 0.1f, true);
}

void ACharacter_Base::OnCollect()
{
	if (bIsHoldingBox == true)
	{
		OnDropBox();
		return;
	}

	OnCollectDelegate.Broadcast();
}

void ACharacter_Base::OnCollectRelease()
{
	bOnCollectDoOnce = true;
}

void ACharacter_Base::OnScore()
{
	//TODO play animation for kick and send notification to clear box and add score and money
	if (bIsAtBoxHolderLocation) 
	{
		OnKickScoreBox();
	}
	return;
}

void ACharacter_Base::OnFire()
{
	SetRunnning(false);

	if (GetCurrentWeapon() == NULL)
	{
		if(CanFire())
			OnPunch();
		return;
	}

	if (!CanFire() || !GetCurrentWeapon()->CanFire())
		return;

	switch (Cast<IGameplayInterface>(GetCurrentWeapon())->Execute_GetWeaponType(GetCurrentWeapon()))
	{
	case EWeaponType::WT_None:
		CharacterState = ECharacterState::CS_Punching;
		PlayAnimationState();
		break;
	case EWeaponType::WT_RocketLauncher:
		CharacterState = ECharacterState::CS_FiringRocket;
		PlayAnimationState();
		FireWeapon();
		break;
	case EWeaponType::WT_MachineGun:
		CharacterState = ECharacterState::CS_Firing;
		PlayAnimationState();
		FireWeapon();
		GetWorldTimerManager().SetTimer(ShootingHandler, this, &ACharacter_Base::FireWeapon, GetCurrentWeapon()->GetWeaponDelay(), true);
		break;
	default:
		break;
	}
	
}

void ACharacter_Base::OnReleaseFire()
{
	//TODO Set Change State Refactor
	if (GetCurrentWeapon() == NULL || !CanFire())
	{
		return;
	}

	switch (Cast<IGameplayInterface>(GetCurrentWeapon())->Execute_GetWeaponType(GetCurrentWeapon()))
	{
	case EWeaponType::WT_None:
		CharacterState = ECharacterState::CS_Walk;
		break;
	case EWeaponType::WT_RocketLauncher:
		CharacterState = ECharacterState::CS_HoldingRocket;
		PlayAnimationState();
		break;
	case EWeaponType::WT_MachineGun:
		CharacterState = ECharacterState::CS_HoldingGun;
		PlayAnimationState();
		GetWorldTimerManager().ClearTimer(ShootingHandler);
		break;
	default:
		break;
	}
	
}

void ACharacter_Base::OnWalk()
{
	//TODO disable if get shot or carrying
	if (CharacterState == ECharacterState::CS_Run)
	{
		CharacterState = ECharacterState::CS_Walk;
		SetRunnning(false);
	}
}

void ACharacter_Base::OnRun()
{
	//TODO if get shot or carrying can't run
	if (CanRun()) 
	{
		CharacterState = ECharacterState::CS_Run;
		SetRunnning(true);
	}
}

void ACharacter_Base::SERVER_SetRunnning_Implementation(bool bNewIsRunning)
{
	SetRunnning(bNewIsRunning);
}

bool ACharacter_Base::SERVER_SetRunnning_Validate(bool bNewIsRunning)
{
	return true;
}

void ACharacter_Base::SetMyPlayerController(APlayerController_Base * MyPlayerControllerRef)
{
	MyPlayerController = MyPlayerControllerRef;
}

APlayerController_Base * ACharacter_Base::GetMyPlayerController()
{
	return MyPlayerController;
}

void ACharacter_Base::SetMyPlayerState(APlayerState_Base * MyPlayerStateRef)
{
	MyPlayerState = MyPlayerStateRef;
}

void ACharacter_Base::SetRunnning(bool bNewIsRunning)
{
	bIsRunning = bNewIsRunning;

	if (Role < ROLE_Authority)
	{
		SERVER_SetRunnning(bNewIsRunning);
	}
}

void ACharacter_Base::SetTargetting(bool bShouldTarget)
{
	bIsTargeting = bShouldTarget;
	if (Role < ROLE_Authority) 
	{
		SERVER_SetTargetting(bShouldTarget);
	}
}

void ACharacter_Base::SERVER_SetTargetting_Implementation(bool bShouldTarget)
{
	SetTargetting(bShouldTarget);
}

bool ACharacter_Base::SERVER_SetTargetting_Validate(bool bShouldTarget)
{
	return true;
}

bool ACharacter_Base::IsRunning() const
{
	if (!GetCharacterMovement())
	{
		return false;
	}

	return bIsRunning;
}

bool ACharacter_Base::IsAlive()
{
	if (Health > 0.0f && !bIsDying) 
	{
		return true;
	}
	return false;
}

bool ACharacter_Base::IsEnemyFor(AController * TestPC) const
{
	if (TestPC == Controller || TestPC == NULL)
	{
		return false;
	}

	bool bIsEnemy = false;

	if (TestPC->IsA(AMyAIController::StaticClass())) 
	{
		bIsEnemy = true;
	}

	///*APlayerState_Base* TestPlayerState = Cast<APlayerState_Base>(TestPC->PlayerState);
	//APlayerState_Base* MyPlayerState = Cast<APlayerState_Base>(PlayerState);
	//if (GetWorld()->GetGameState())
	//{
	//	const AMyGameMode_Base* DefGame = GetWorld()->GetGameState()->GetDefaultGameMode<AMyGameMode_Base>();
	//	if (DefGame && MyPlayerState && TestPlayerState)
	//	{
	//		bIsEnemy = DefGame->CanDealDamage(TestPlayerState, MyPlayerState);
	//	}
	//}*/
	//return bIsEnemy;

	return bIsEnemy;

}

bool ACharacter_Base::SetIsAtBoxLocation(bool bIsNearLocation)
{
	bIsAtBoxHolderLocation = bIsNearLocation;
	return bIsNearLocation;
}

void ACharacter_Base::MULTICAST_PlayAnimMontage_Implementation(UAnimMontage * Montage, float InPlayRate, FName StartSectionName)
{
	ACharacter::PlayAnimMontage(Montage, InPlayRate, StartSectionName);
	return;
}

void ACharacter_Base::SERVER_PlayAnimMontage_Implementation(UAnimMontage * Montage, float InPlayRate, FName StartSectionName)
{
	MULTICAST_PlayAnimMontage(Montage, InPlayRate, StartSectionName);
	return;
}

bool ACharacter_Base::SERVER_PlayAnimMontage_Validate(UAnimMontage * Montage, float InPlayRate, FName StartSectionName)
{
	return true;
}

void ACharacter_Base::SERVER_UseLootable_Implementation()
{
	UseLootable();
}

bool ACharacter_Base::SERVER_UseLootable_Validate()
{
	return true;
}

void ACharacter_Base::UseLootable_Implementation()
{
	if (Role < ROLE_Authority)
	{
		SERVER_UseLootable();
		return;
	}
	OnUseLootableDelegate.Broadcast();
}

bool ACharacter_Base::SphereTraceLootable()
{
	const FVector StaticLocation = GetActorLocation();;
	const float SphereRadius = 200.0f;

	FCollisionQueryParams TraceParams(FName(TEXT("Lootable trace")), true, NULL);
	TraceParams.bTraceComplex = true;
	TraceParams.bReturnPhysicalMaterial = false;
	TraceParams.AddIgnoredActor(this);
	
	GetWorld()->SweepMultiByChannel(LootableOutHit, StaticLocation, StaticLocation, FQuat(), ECollisionChannel::ECC_GameTraceChannel4, FCollisionShape::MakeSphere(SphereRadius), TraceParams);

	if (LootableOutHit.Num() > 0)
	{
		if (bBindDynamicDoOnce) 
		{
			OnCollectDelegate.AddDynamic(this, &ACharacter_Base::CollectItem);
			bBindDynamicDoOnce = false;
		}
		IHighlightInterface* HInterface = Cast<IHighlightInterface>(GetCurrentSelectedItem().GetActor());
		if (HInterface) 
		{
			HInterface->Execute_HighLightActor(GetCurrentSelectedItem().GetActor());
		}
		/*DEBUG*/
		DrawSphereDebugLine(SphereRadius, StaticLocation, FColor::Red);
		return true;
	}
	else 
	{
		/*DEBUG*/
		DrawSphereDebugLine(SphereRadius, StaticLocation, FColor::Green);

		OnCollectDelegate.Clear();
		bBindDynamicDoOnce = true;
		return false;
	}

	return false;
}

void ACharacter_Base::DrawSphereDebugLine(float Radius, FVector CenterLocation, FColor Color)
{
	if (bEnableLootableSphere) 
	{
		UKismetSystemLibrary::DrawDebugSphere(GetWorld(), CenterLocation, Radius, 9, Color, 0.05f, 1.0f );
	}
}

void ACharacter_Base::UpdateColor(APlayerState_Base* PState, USkeletalMeshComponent* SMesh)
{
	if (Role < ROLE_Authority) 
	{
		SERVER_UpdateColor(PState, SMesh);
		return;
	}
	MULTICAST_UpdateColor(PState, SMesh);
}

void ACharacter_Base::SERVER_UpdateColor_Implementation(APlayerState_Base* PState, USkeletalMeshComponent* SMesh)
{
	UpdateColor(PState, SMesh);
}

bool ACharacter_Base::SERVER_UpdateColor_Validate(APlayerState_Base* PState, USkeletalMeshComponent* SMesh)
{
	return true;
}

void ACharacter_Base::MULTICAST_UpdateColor_Implementation(APlayerState_Base* PState, USkeletalMeshComponent* SMesh)
{
	if (PState != NULL)
	{
		uint8 TeamNum = PState->GetTeamNum();
		switch (TeamNum)
		{
		case 1:
			SMesh->SetMaterial(0, TeamColorMat[0]);
			break;
		case 2:
			SMesh->SetMaterial(0, TeamColorMat[1]);
			break;
		case 3:
			SMesh->SetMaterial(0, TeamColorMat[2]);
			break;
		case 4:
			SMesh->SetMaterial(0, TeamColorMat[3]);
			break;
		}
	}
}

FHitResult ACharacter_Base::GetCurrentSelectedItem()
{
	if (LootableOutHit.Num() <= 0)
	{
		return FHitResult();
	}

	int32 SelectedItemIndexCalculation = LootableOutHit.Num() == 1 ? 0 : SelectedItemIndex % (LootableOutHit.Num());
	return LootableOutHit[SelectedItemIndexCalculation];
}

void ACharacter_Base::CollectItem()
{
	if (CanLoot()) 
	{
		LootableFilter();
	}

	bOnCollectDoOnce = false;
}

void ACharacter_Base::SERVER_OnScore_Implementation()
{
	OnKickScoreBox();
}

bool ACharacter_Base::SERVER_OnScore_Validate()
{
	return true;
}

void ACharacter_Base::OnKickScoreBox()
{
	if (Role < ROLE_Authority)
	{
		SERVER_OnScore();
		return;
	}

	AMyGameState_Base* GS = Cast<AMyGameState_Base>(GetWorld()->GetGameState());
	if (GS) 
	{
		int32 AmountOfBoxes = MyPlayerState->GetSpawnLocation()->GetNumOfBox();
		if (AmountOfBoxes <= 0)
			return;

		//float CurrencyAdded = (float)AmountOfBoxes + MyPlayerState->GetPlayerCurrency();
		float ScoreAdded = (float)AmountOfBoxes + MyPlayerState->GetPlayerScore();
		float CurrencyAdded = (((float)AmountOfBoxes - 0.5f) * 5) + MyPlayerState->GetPlayerCurrency();

		MyPlayerState->SetPlayerCurrency(CurrencyAdded);
		MyPlayerState->SetPlayerScore(ScoreAdded);

		MyPlayerState->GetSpawnLocation()->DestroyBox();
		GS->CheckScore();
	}
}

void ACharacter_Base::OnRep_MyPlayerController()
{
}

void ACharacter_Base::OnRep_Stamina_Implementation()
{

}

void ACharacter_Base::RegenStamina()
{
	if (bShouldRegenStamina) 
	{
		SetStamina(GetStaminaVal() + (GetWorld()->GetDeltaSeconds() * RegenRate), false);
		//Stamina += GetWorld()->GetDeltaSeconds() * RegenRate;
		//stop Regen if over MaxStamina
		if (GetStaminaVal() >= MaxStamina)
		{
			SetStamina(MaxStamina, false);
			bShouldRegenStamina = false;
		}
	}
}

void ACharacter_Base::TriggerRegenStamina()
{
	bShouldRegenStamina = true;
}

void ACharacter_Base::SERVER_SetStaminaVal_Implementation(float NewVal)
{
	SetStamina(NewVal, false);
}

bool ACharacter_Base::SERVER_SetStaminaVal_Validate(float NewVal)
{
	return true;
}

void ACharacter_Base::OnRep_MyPlayerState()
{
	UpdateColor(MyPlayerState, GetMesh());
}

float ACharacter_Base::SetStamina(float StaminaVal, bool DrainStamina)
{
	/*Cheating*/
	if (bStaminaCheatEnabled) 
	{
		Stamina = 100.0f;
		return Stamina;
	}
	/*-------------*/
	/*Happen Locally*/
	if (DrainStamina)
	{
		bShouldRegenStamina = false;
		GetWorldTimerManager().SetTimer(DelayStaminaRegenHandle, this, &ACharacter_Base::TriggerRegenStamina, DelayBeforeRegenStamina, false);
	}
	/*-------------*/
	if (Role < ROLE_Authority)
	{
		SERVER_SetStaminaVal(StaminaVal);
		return StaminaVal;
	}
	Stamina = StaminaVal;

	if (Stamina < 0.0f)
		Stamina = 0.0f;

	OnRep_Stamina();
	return Stamina;
}

void ACharacter_Base::OnRep_Health_Implementation()
{
}

void ACharacter_Base::OnDeathNotify_Implementation()
{
	//Check if Is AI
	if (GetMyPlayerController()->IsValidLowLevel())
	{
		DisableInput(MyPlayerController);
		bIsDying = true;
		//TODO Check for Available Currency, Deduct from there
		//TODO Delete ALL Inventory
		if (MyPlayerState->GetPlayerCurrency() >= 5.0f)
			MyPlayerState->SetPlayerCurrency(MyPlayerState->GetPlayerCurrency() - 5.0f);
		else
			MyPlayerState->SetPlayerCurrency(0.0f);

		PlayAnimationState();
		GetWorldTimerManager().SetTimer(DeathTimeHandler, this, &ACharacter_Base::OnDeathNotifyTimerRespawn, 2.0f, false);
	}
	else 
	{
		//TODO Spawn Drops
		UnPossessed();
		GetWorldTimerManager().SetTimer(DeathTimeHandler, this, &ACharacter_Base::RemoveAI, 2.0f, false);
	}
}

void ACharacter_Base::OnKill()
{
}

bool ACharacter_Base::CanRun()
{
	if (bIsPunching || bIsHoldingBox || bIsTargeting || Stamina <= 0.0f)
	{
		return false;
	}
	return true;
}

bool ACharacter_Base::bSetOnSimulatePhysic( AActor * ActorToSimulate, bool bShouldSimulate)
{
	if (Role < ROLE_Authority) 
	{
		SERVER_SetOnSimulatePhysic(ActorToSimulate,bShouldSimulate);
		return bShouldSimulate;
	}

	AMyBox* MyBoxActor = Cast<AMyBox>(ActorToSimulate);
	MyBoxActor->bSetSimulatePhysic(bShouldSimulate);
	return bShouldSimulate;
}

void ACharacter_Base::SERVER_SetOnSimulatePhysic_Implementation(AActor* ActorToSimulate, bool bShouldSimulate)
{
	bSetOnSimulatePhysic(ActorToSimulate, bShouldSimulate);
}

bool ACharacter_Base::SERVER_SetOnSimulatePhysic_Validate(AActor* ActorToSimulate, bool bShouldSimulate)
{
	return true;
}

void ACharacter_Base::MULTICAST_StopAnimMontage_Implementation(UAnimMontage * Montage)
{
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying())
		ACharacter::StopAnimMontage(Montage);
}

void ACharacter_Base::SERVER_StopAnimMontage_Implementation(UAnimMontage * Montage)
{
	MULTICAST_StopAnimMontage(Montage);
}

bool ACharacter_Base::SERVER_StopAnimMontage_Validate(UAnimMontage * Montage)
{
	return true;
}

void ACharacter_Base::MULTICAST_SwitchAnimMontage_Implementation(FName CurrentSection, FName NextSection, UAnimMontage * Montage)
{
	GetMesh()->GetAnimInstance()->Montage_SetNextSection(CurrentSection, NextSection, Montage);
}

void ACharacter_Base::SERVER_SwitchAnimMontage_Implementation(FName CurrentSection, FName NextSection, UAnimMontage * Montage)
{
	MULTICAST_SwitchAnimMontage( CurrentSection, NextSection, Montage);
}

bool ACharacter_Base::SERVER_SwitchAnimMontage_Validate(FName CurrentSection, FName NextSection, UAnimMontage * Montage)
{
	return true;
}

void ACharacter_Base::PlayAnimationState()
{
	//*Animation States need a better Refactor *//
	if (bIsDying)
	{
		print("Died");
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Died"));
		SERVER_PlayAnimMontage(DeathMontage, 1.0f, "Default");
		return;
	}
	switch (CharacterState)
	{
	case ECharacterState::CS_Walk:
		SERVER_StopAnimMontage(GetCurrentMontage());
		break;
	case ECharacterState::CS_Carry:
		SERVER_StopAnimMontage(GetCurrentMontage());
		SERVER_PlayAnimMontage(CarryingBoxMontage, 1.0f, "Default");
		break;
	case ECharacterState::CS_Firing:
		//TODO Fix This Part
		SERVER_StopAnimMontage(GetCurrentMontage());
		SERVER_PlayAnimMontage(ShootingMontage, 1.0f, "StartShooting");
		break;
	case ECharacterState::CS_FiringRocket:
		SERVER_StopAnimMontage(GetCurrentMontage());
		SERVER_PlayAnimMontage(RocketLauncherMontage, 1.0f, "StartShooting");
		SERVER_SwitchAnimMontage("StartShooting", "HoldingRocket", RocketLauncherMontage);
		break;
	case ECharacterState::CS_HoldingGun:
		SERVER_StopAnimMontage(GetCurrentMontage());
		SERVER_PlayAnimMontage(ShootingMontage, 1.0f, "HoldingGun");
		//SERVER_SwitchAnimMontage("StartShooting", "HoldingGun", ShootingMontage);
		break;
	case ECharacterState::CS_HoldingRocket:
		SERVER_StopAnimMontage(GetCurrentMontage());
		SERVER_PlayAnimMontage(RocketLauncherMontage, 1.0f, "HoldingRocket");
		//SERVER_SwitchAnimMontage("StartShooting", "HoldingRocket", RocketLauncherMontage);
		break;
	case ECharacterState::CS_Punching:
		SERVER_PlayAnimMontage(PunchingMontage, 1.0f, "StartPunching");
		break;
	case ECharacterState::CS_Targetting:
		break;
	default:
		break;
	}
	
}

void ACharacter_Base::PlayTypeOfWeaponAnimation(EWeaponType WeaponType)
{
	switch (WeaponType)
	{
	case EWeaponType::WT_MachineGun:
		SERVER_StopAnimMontage(GetCurrentMontage());
		SERVER_PlayAnimMontage(ShootingMontage, 1.0f, "HoldingGun");
		break;
	case EWeaponType::WT_RocketLauncher:
		SERVER_StopAnimMontage(GetCurrentMontage());
		SERVER_PlayAnimMontage(RocketLauncherMontage, 1.0f, "HoldingRocket");
		break;
	default:
		break;
	}
}

void ACharacter_Base::OnHoldBox()
{
	CharacterState = ECharacterState::CS_Carry;
	SetRunnning(false);

	//TODO Change from Selection from Array % with the highest number and increment
	MyHoldingBox = Cast<AMyBox>(GetCurrentSelectedItem().GetActor());
	UStaticMeshComponent* StaticMeshComponent = MyHoldingBox->GetStaticMesh();
	IGameplayInterface* GameplayInterface = Cast<IGameplayInterface>(GetCurrentSelectedItem().GetActor());

	bSetOnSimulatePhysic(MyHoldingBox , false);
	SetOnHoldAndDropCollision(StaticMeshComponent, ECR_Ignore);
	AttachActorToMesh(MyHoldingBox);

	bIsHoldingBox = true;
	PlayAnimationState();

	if (GetCurrentWeapon() != NULL)
	{
		SetWeaponVisible(GetCurrentWeapon(), false);
	}
}

void ACharacter_Base::OnDropBox()
{
	bIsHoldingBox = false;
	UStaticMeshComponent* StaticMeshComponent = MyHoldingBox->GetStaticMesh();
	DetachActorFromMesh(MyHoldingBox);
	//Snap it to the Box Holder
	if (!bIsAtBoxHolderLocation) 
	{
		SetOnHoldAndDropCollision(StaticMeshComponent,ECR_Block);
		bSetOnSimulatePhysic(MyHoldingBox, true);
	}
	else 
	{
		OnSnapBoxToLocation(MyHoldingBox);
	}

	CharacterState = ECharacterState::CS_Walk;
	PlayAnimationState();

	if (GetCurrentWeapon() != NULL)
	{
		//TODO set function to Set Character State
		EWeaponType WeaponType;
		IGameplayInterface* GameplayInterface = Cast<IGameplayInterface>(GetCurrentWeapon());
		WeaponType = GameplayInterface->Execute_GetWeaponType(GetCurrentWeapon());
		PlayTypeOfWeaponAnimation(WeaponType);
		SetWeaponVisible(GetCurrentWeapon(), true);
	}
}

bool ACharacter_Base::CanLoot()
{
	if (CharacterState == ECharacterState::CS_Carry) 
	{
		return false;
	}
	return true;
}

void ACharacter_Base::SERVER_OnSnapBoxToLocation_Implementation(AMyBox * BoxToSnapTo)
{
	OnSnapBoxToLocation(BoxToSnapTo);
}

bool ACharacter_Base::SERVER_OnSnapBoxToLocation_Validate(AMyBox * BoxToSnapTo)
{
	return true;
}

void ACharacter_Base::OnSnapBoxToLocation(AMyBox* BoxToSnapTo)
{
	if (Role < ROLE_Authority) 
	{
		SERVER_OnSnapBoxToLocation(BoxToSnapTo);
		return;
	}
	SetLootableCollision(BoxToSnapTo->GetStaticMesh(), ECollisionChannel::ECC_GameTraceChannel5, ECR_Ignore);
	MyPlayerState->GetSpawnLocation()->SnapBoxToTarget(this, BoxToSnapTo);
}

void ACharacter_Base::LootableFilter()
{
	if (LootableOutHit.Num() > 0)
	{
		IGameplayInterface* GameplayInterface = Cast<IGameplayInterface>(GetCurrentSelectedItem().GetActor());
		if (GameplayInterface)
		{
			ELootAbleType LootableType = GameplayInterface->Execute_GetLootableType(GetCurrentSelectedItem().GetActor());
			switch (LootableType)
			{
			case ELootAbleType::LAT_Weapon:
				OnLootWeapon();
				break;
			case ELootAbleType::LAT_PowerUp:
				OnLootLootable(Cast<ALoot_Base>(GetCurrentSelectedItem().GetActor()));
				break;
			case ELootAbleType::LAT_Box:
				OnHoldBox();
				break;
			default:
				break;
			}
		}
	}
}

bool ACharacter_Base::CanFire()
{
	if (GetCurrentWeapon() != NULL || !bIsRunning || !bIsHoldingBox)
	{
		if (GetCurrentWeapon()->IsValidLowLevel()) 
		{
			if (GetCurrentWeapon()->GetStaminaCost() > GetStaminaVal())
				return false;
		}
		return true;
	}

	return false;
}

AWeapon_Base* ACharacter_Base::GetCurrentWeapon()
{
	if (!WeaponArray.IsValidIndex(0) || !WeaponArray.IsValidIndex(CurrentWeaponIndex))
		return NULL;

	return Cast<AWeapon_Base>(WeaponArray[CurrentWeaponIndex]);
}

void ACharacter_Base::OnChangeWeapon()
{
	if (GetCurrentWeapon()->IsValidLowLevel()) 
	{
		EWeaponType WeaponType;
		IGameplayInterface* GameplayInterface = Cast<IGameplayInterface>(GetCurrentWeapon());
		if (GameplayInterface) 
		{
			WeaponType = GameplayInterface->Execute_GetWeaponType(GetCurrentWeapon());
			PlayTypeOfWeaponAnimation(WeaponType);
			SetCurrentWeapon(GetCurrentWeapon());
		}
	}
	else 
	{
		SetCurrentWeapon(NULL);
		CharacterState = ECharacterState::CS_Walk;
		PlayAnimationState();
	}
}

void ACharacter_Base::OnLootWeapon()
{
	if (WeaponArray.Num() == MaxNumOfWeapon) 
	{
		print("BEEP BEEP: Max Inventory");
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT(""));
		return;
	}
	AWeapon_Base* Weapon;
	TArray<UStaticMeshComponent*> StaticMeshComponents;

	Weapon = Cast<AWeapon_Base>(GetCurrentSelectedItem().GetActor());
	Weapon->GetComponents<UStaticMeshComponent>(StaticMeshComponents);
	AddWeaponIntoArray(Weapon);

	SetWeaponVisible(Weapon,false);
	SetOnHoldAndDropCollision(StaticMeshComponents[0], ECR_Ignore);
	AttachActorToMesh(Weapon);

	OnChangeWeapon();
}

void ACharacter_Base::OnPunch()
{
	bIsPunching = true;
	TArray<FAnimNotifyEvent> StartPunchNotify = PunchingMontage->Notifies;
	GetWorldTimerManager().SetTimer(PunchingHandler, this, &ACharacter_Base::OnPunchNotify, StartPunchNotify[0].GetTriggerTime(), false);
	if (Role < ROLE_Authority) 
	{
		SERVER_OnPunch();
		return;
	}
	CharacterState = ECharacterState::CS_Punching;
	PlayAnimationState();

	//TArray<FAnimNotifyEvent> StartPunchNotify = PunchingMontage->Notifies;
	//GetWorldTimerManager().SetTimer(PunchingHandler, this, &ACharacter_Base::OnPunchNotify, StartPunchNotify[0].GetTriggerTime(), false);
	
}

void ACharacter_Base::OnPunchNotify()
{
	bIsPunching = false;
	//TODO Deal Damage here
	FVector StartPoint = this->GetActorLocation();
	FVector EndPoint = StartPoint + (GetActorForwardVector() * 150);
	FHitResult HitData(ForceInit);
	FHitResult DamageInfo(ForceInit);

	print("ONE PUNCH");
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("ONE PUNCH"));
	if (UMyBlueprintFunctionLibrary::Trace(GetWorld(), this, StartPoint, EndPoint, HitData, ECC_Visibility, false))
	{
		UGameplayStatics::ApplyPointDamage(HitData.Actor.Get(), 10.0f, HitData.ImpactNormal, DamageInfo, GetController(), this, OnePunchDamageClass);
	}
	
	//CharacterState = ECharacterState::CS_Walk;
}

void ACharacter_Base::AttachActorToMesh(AActor * ActorToAttach)
{
	IGameplayInterface* GameplayInterface = Cast<IGameplayInterface>(ActorToAttach);
	switch (GameplayInterface->Execute_GetLootableType(ActorToAttach))
	{
	case ELootAbleType::LAT_Weapon:
		ActorToAttach->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "GunHolder");
		//MULTICAST_AttachEquip(ActorToAttach, "GunHolder");
		break;
	case ELootAbleType::LAT_Box:
		ActorToAttach->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "ItemHolder");
		//MULTICAST_AttachEquip(ActorToAttach, "ItemHolder");
		break;
	default:
		break;
	}
	if (Role < ROLE_Authority) 
	{
		SERVER_AttachEquip(ActorToAttach);
	}
}

void ACharacter_Base::DetachActorFromMesh(AActor * ActorToDettach)
{
	ActorToDettach->bReplicateMovement = true;
	ActorToDettach->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	//ActorToDettach->SetLifeSpan(180.0f);
	if (Role < ROLE_Authority)
	{
		SERVER_DettachEquip(ActorToDettach);
	}
}

void ACharacter_Base::SetLootableCollision(UStaticMeshComponent * ActorComponentToSet, ECollisionChannel SetChannel, ECollisionResponse ChannelResponse)
{
	if (Role < ROLE_Authority)
	{
		SERVER_SetCollision(ActorComponentToSet, SetChannel, ChannelResponse);
		return;
	}
	MULTICAST_SetCollision(ActorComponentToSet, SetChannel, ChannelResponse);
}

void ACharacter_Base::SetOnHoldAndDropCollision(UStaticMeshComponent* StaticMeshComponent, ECollisionResponse ChannelResponse)
{
	SetLootableCollision(StaticMeshComponent, ECollisionChannel::ECC_GameTraceChannel4, ChannelResponse);
	SetLootableCollision(StaticMeshComponent, ECollisionChannel::ECC_WorldDynamic, ChannelResponse);
	SetLootableCollision(StaticMeshComponent, ECollisionChannel::ECC_WorldStatic, ChannelResponse);
	SetLootableCollision(StaticMeshComponent, ECollisionChannel::ECC_Visibility, ChannelResponse);
}

void ACharacter_Base::AddWeaponIntoArray(AWeapon_Base* Weapon)
{
	Weapon->SetPawnOwner(GetController());
	MyPlayerController->SetActorOwner(Weapon, MyPlayerController);
	//Weapon->SetOwner(this);
	Inventory.Weapon.Add(Weapon->GetClass());
	WeaponArray.Add(Weapon);
	UpdateInventoryUIDelegate.Broadcast();

}

void ACharacter_Base::OnDeathNotifyTimerRespawn()
{
	MyPlayerController->RespawnPlayer();
}

void ACharacter_Base::RemoveAI()
{
	Destroy();
}

void ACharacter_Base::SERVER_OnPunch_Implementation()
{
	OnPunch();
}

bool ACharacter_Base::SERVER_OnPunch_Validate() 
{
	return true;
}

void ACharacter_Base::SERVER_AttachEquip_Implementation(AActor* ActorToAttach)
{
	AttachActorToMesh(ActorToAttach);
}

bool ACharacter_Base::SERVER_AttachEquip_Validate(AActor* ActorToAttach)
{
	return true;
} 

void ACharacter_Base::SERVER_SetCollision_Implementation(UStaticMeshComponent * ActorComponentToSet, ECollisionChannel SetChannel, ECollisionResponse ChannelResponse)
{
	SetLootableCollision(ActorComponentToSet, SetChannel, ChannelResponse);
}

bool ACharacter_Base::SERVER_SetCollision_Validate(UStaticMeshComponent * ActorComponentToSet, ECollisionChannel SetChannel, ECollisionResponse ChannelResponse)
{
	return true;
}

void ACharacter_Base::SetWeaponVisible(AWeapon_Base* WeaponToHide, bool bShouldBeVisible)
{
	if (Role < ROLE_Authority)
	{
		SERVER_SetWeaponVisible(WeaponToHide, bShouldBeVisible);
		return;
	}
	WeaponToHide->SetActorHiddenInGame(!bShouldBeVisible);
}

void ACharacter_Base::SERVER_SetWeaponVisible_Implementation(AWeapon_Base* WeaponToHide, bool bShouldBeVisible)
{
	SetWeaponVisible(WeaponToHide, bShouldBeVisible);
}

bool ACharacter_Base::SERVER_SetWeaponVisible_Validate(AWeapon_Base* WeaponToHide, bool bShouldBeVisible)
{
	return true;
}

void ACharacter_Base::SERVER_DettachEquip_Implementation(AActor * ActorToDettach)
{
	DetachActorFromMesh(ActorToDettach);
}

bool ACharacter_Base::SERVER_DettachEquip_Validate(AActor * ActorToDettach)
{
	return true;
}

void ACharacter_Base::MULTICAST_SetCollision_Implementation(UStaticMeshComponent * ActorComponentToSet, ECollisionChannel SetChannel, ECollisionResponse ChannelResponse)
{
	if (ActorComponentToSet->IsValidLowLevel())
		ActorComponentToSet->SetCollisionResponseToChannel(SetChannel, ChannelResponse);
}

void ACharacter_Base::FireWeapon()
{
	if (GetCurrentWeapon()->IsValidLowLevel())
		GetCurrentWeapon()->FireWeapon();
}

void ACharacter_Base::SetCurrentWeapon(AWeapon_Base* Weapon)
{
	if (PreviousWeapon->IsValidLowLevel() && !bDropWeapon)
	{
		PreviousWeapon = CurrentWeapon;
		/*To Check if it's not NULL After Conversion*/
		if (PreviousWeapon->IsValidLowLevel())
			SetWeaponVisible(PreviousWeapon, false);
	}
	else
	{
		PreviousWeapon = Weapon;
	}
	CurrentWeapon = Weapon;

	if(CurrentWeapon->IsValidLowLevel())
		SetWeaponVisible(CurrentWeapon, true);
}

void ACharacter_Base::OnLootLootable(ALoot_Base* LootableItem)
{
	if (Role < ROLE_Authority) 
	{
		SERVER_OnLootLootable(LootableItem);
		return;
	}
	Inventory.PowerUp.Add(LootableItem->GetClass());
	MULTICAST_OnLootLootable(LootableItem);
}

void ACharacter_Base::MULTICAST_OnLootLootable_Implementation(ALoot_Base* LootableItem)
{
	LootableItem->OnPickUp();
}

void ACharacter_Base::SERVER_OnLootLootable_Implementation(ALoot_Base* LootableItem)
{
	OnLootLootable(LootableItem);
}

bool ACharacter_Base::SERVER_OnLootLootable_Validate(ALoot_Base* LootableItem)
{
	return true;
}
