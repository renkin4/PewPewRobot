// YangIsAwesome

#include "Character_Base.h"
#include "MyCharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine.h"
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

// Sets default values
//Constructor
ACharacter_Base::ACharacter_Base(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UMyCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	RunningSpeedModifier = 1.8f;
	WalkSpeedModifier = 1.0f;
	bIsRunning = false;
	CharacterState = ECharacterState::CS_Walk;
	Inventory.bIsWeaponExist = false;
	bBindDynamicDoOnce = true;
	bOnCollectDoOnce = true;
	MaxHealth = 100.0f;
	Health = MaxHealth;
	LocalHealth = Health;
	bDie = false;
	bIsDying = false;
	bIsHoldingBox = false;
	bIsAtBoxHolderLocation = false;
	SelectedItemIndex = 0;

	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

void ACharacter_Base::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(ACharacter_Base, bIsRunning, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(ACharacter_Base, MyPlayerState, COND_None);
	DOREPLIFETIME_CONDITION(ACharacter_Base, bIsAtBoxHolderLocation, COND_None);
	DOREPLIFETIME_CONDITION(ACharacter_Base, MyPlayerController, COND_None);
	DOREPLIFETIME_CONDITION(ACharacter_Base, MaxHealth, COND_None);
	DOREPLIFETIME_CONDITION(ACharacter_Base, Health, COND_None);
}

float ACharacter_Base::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float ActualDamage;
	//IgnoreOnDeath
	if (bIsDying)
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

// Called when the game starts or when spawned
void ACharacter_Base::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACharacter_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SphereTraceLootable();
	if (GetMyPlayerController()->IsValidLowLevel()) 
	{
		bIsTargeting = GetMyPlayerController()->GetIsAiming();
	}
}

// Called to bind functionality to input
void ACharacter_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	/*Bind Delegate input to functions*/
	if (PlayerInputComponent->IsValidLowLevel())
	{

		PlayerInputComponent->BindAxis("Forward", this, &ACharacter_Base::MoveForward);
		PlayerInputComponent->BindAxis("Right", this, &ACharacter_Base::MoveRight);
		PlayerInputComponent->BindAxis("LookUp", this, &ACharacter_Base::PitchLookUp);
		PlayerInputComponent->BindAxis("Turn", this, &ACharacter_Base::YawTurn);

		PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter_Base::OnJump);
		PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ACharacter_Base::OnFire);
		PlayerInputComponent->BindAction("Fire", IE_Released, this, &ACharacter_Base::OnReleaseFire);
		PlayerInputComponent->BindAction("Collect", IE_Pressed, this, &ACharacter_Base::OnCollect);
		PlayerInputComponent->BindAction("Collect", IE_Released, this, &ACharacter_Base::OnCollectRelease);
		PlayerInputComponent->BindAction("Score", IE_Pressed, this, &ACharacter_Base::OnScore);
		PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ACharacter_Base::OnAim);
		PlayerInputComponent->BindAction("Aim", IE_Released, this, &ACharacter_Base::OnReleasedAim);
		PlayerInputComponent->BindAction("SpeedRun", IE_Pressed, this, &ACharacter_Base::OnRun);
		PlayerInputComponent->BindAction("SpeedRun", IE_Released, this, &ACharacter_Base::OnWalk);
		PlayerInputComponent->BindAction("UseLootable", IE_Pressed, this, &ACharacter_Base::OnUseLootable);
		PlayerInputComponent->BindAction("SwitchSelection", IE_Pressed, this, &ACharacter_Base::OnSwitchSelection);

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
	if (!CanFire() && !CurrentWeapon->CanFire())
		return;

	if (CurrentWeapon == NULL) 
	{
		OnPunch();
		return;
	}

	switch (Cast<IGameplayInterface>(CurrentWeapon)->Execute_GetWeaponType(CurrentWeapon))
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
		//TODO change to Event Notify From Animation
		GetWorldTimerManager().SetTimer(ShootingHandler, this, &ACharacter_Base::FireWeapon, CurrentWeapon->GetWeaponDelay(), true);
		break;
	default:
		break;
	}
	
}

void ACharacter_Base::OnReleaseFire()
{
	//TODO Set Change State Refactor
	if (CurrentWeapon == NULL || !CanFire())
	{
		return;
	}

	switch (Cast<IGameplayInterface>(CurrentWeapon)->Execute_GetWeaponType(CurrentWeapon))
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
	FVector StaticLocation = GetActorLocation();;
	float SphereRadius = 200.0f;

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
		DrawDebugSphere(GetWorld(), CenterLocation, Radius, 9, Color, false, 0.05f,0, 1.0f );
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
		{
			return;
		}
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

void ACharacter_Base::OnRep_MyPlayerState()
{
}

void ACharacter_Base::OnRep_Health_Implementation()
{

}

void ACharacter_Base::OnDeathNotify_Implementation()
{
	DisableInput(MyPlayerController);
	bIsDying = true;
	PlayAnimationState();
	GetWorldTimerManager().SetTimer(DeathTimeHandler, this, &ACharacter_Base::OnDeathNotifyTimerRespawn, 2.0f, false);
}

bool ACharacter_Base::CanRun()
{
	if (bIsHoldingBox || bIsTargeting)
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
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Died"));
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

	TArray<UStaticMeshComponent*> StaticMeshComponents;
	IGameplayInterface* GameplayInterface = Cast<IGameplayInterface>(LootableOutHit[0].Actor.Get());

	//TODO Change from Selection from Array % with the highest number and increment
	MyHoldingBox = Cast<AMyBox>(LootableOutHit[0].Actor.Get());
	MyHoldingBox->GetComponents<UStaticMeshComponent>(StaticMeshComponents);

	bSetOnSimulatePhysic(MyHoldingBox , false);
	AttachActorToMesh(MyHoldingBox);
	SetLootableCollision(StaticMeshComponents[0], ECollisionChannel::ECC_GameTraceChannel4, ECR_Ignore);


	if (CurrentWeapon != NULL)
	{
		SetWeaponVisible(CurrentWeapon, false);
	}

	bIsHoldingBox = true;
	PlayAnimationState();
}

void ACharacter_Base::OnDropBox()
{
	bIsHoldingBox = false;
	TArray<UStaticMeshComponent*> StaticMeshComponents;

	MyHoldingBox->GetComponents<UStaticMeshComponent>(StaticMeshComponents);
	DetachActorFromMesh(MyHoldingBox);
	//Snap it to the Box Holder
	if (!bIsAtBoxHolderLocation) 
	{
		SetLootableCollision(StaticMeshComponents[0], ECollisionChannel::ECC_GameTraceChannel4, ECR_Block);
		bSetOnSimulatePhysic(MyHoldingBox, true);
	}
	else 
	{
		OnSnapBoxToLocation(MyHoldingBox);
	}

	if (CurrentWeapon != NULL)
	{
		//TODO set function to Set Character State
		CharacterState = ECharacterState::CS_HoldingGun;
		SetWeaponVisible(CurrentWeapon, true);
	}

	CharacterState = ECharacterState::CS_Walk;
	PlayAnimationState();
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
		IGameplayInterface* GameplayInterface = Cast<IGameplayInterface>(LootableOutHit[0].Actor.Get());
		if (GameplayInterface)
		{
			ELootAbleType LootableType = GameplayInterface->Execute_GetLootableType(LootableOutHit[0].Actor.Get());
			switch (LootableType)
			{
			case ELootAbleType::LAT_Weapon:
				OnLootWeapon();
				break;
			case ELootAbleType::LAT_PowerUp:
				OnLootLootable(this);
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
	if ((CurrentWeapon != NULL || CharacterState != ECharacterState::CS_Run) && bIsHoldingBox == false)
	{
		return true;
	}

	return false;
}

void ACharacter_Base::OnLootWeapon()
{
	AWeapon_Base* Weapon;
	EWeaponType WeaponType;
	TArray<UStaticMeshComponent*> StaticMeshComponents;
	IGameplayInterface* GameplayInterface = Cast<IGameplayInterface>(LootableOutHit[0].Actor.Get());

	//TODO Change from Selection from Array % with the highest number and increment
	Weapon = Cast<AWeapon_Base>(GetCurrentSelectedItem().Actor.Get());
	WeaponType = GameplayInterface->Execute_GetWeaponType(Weapon);
	Weapon->GetComponents<UStaticMeshComponent>(StaticMeshComponents);

	Weapon->SetPawnOwner(GetController());
	Inventory.Weapon.Add(Weapon);
	SetCurrentWeapon(Weapon);

	AttachActorToMesh(Weapon);
	SetLootableCollision(StaticMeshComponents[0], ECollisionChannel::ECC_GameTraceChannel4, ECR_Ignore);

	PlayTypeOfWeaponAnimation(WeaponType);
	
}

void ACharacter_Base::OnPunch()
{
	if (Role < ROLE_Authority) 
	{
		SERVER_OnPunch();
	}
	else 
	{
		CharacterState = ECharacterState::CS_Punching;
		PlayAnimationState();

		TArray<FAnimNotifyEvent> StartPunchNotify = PunchingMontage->Notifies;
		GetWorldTimerManager().SetTimer(PunchingHandler, this, &ACharacter_Base::OnPunchNotify, StartPunchNotify[0].GetTriggerTime(), false);
	}
}

void ACharacter_Base::OnPunchNotify()
{
	//TODO Deal Damage here
	FVector StartPoint = this->GetActorLocation();
	FVector EndPoint = StartPoint + (GetActorForwardVector() * 150);
	FHitResult HitData(ForceInit);
	FHitResult DamageInfo(ForceInit);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("ONE PUNCH"));
	if (UMyBlueprintFunctionLibrary::Trace(GetWorld(), this, StartPoint, EndPoint, HitData, ECC_Visibility, false))
	{
		UGameplayStatics::ApplyPointDamage(HitData.Actor.Get(), 10.0f, HitData.ImpactNormal, DamageInfo, GetController(), this, OnePunchDamageClass);
	}
	
	//CharacterState = ECharacterState::CS_Walk;
}

void ACharacter_Base::AttachActorToMesh(AActor * ActorToAttach)
{
	if (Role < ROLE_Authority) 
	{
		SERVER_AttachEquip(ActorToAttach);
	}
	else 
	{
		IGameplayInterface* GameplayInterface = Cast<IGameplayInterface>(ActorToAttach);
		switch (GameplayInterface->Execute_GetLootableType(ActorToAttach))
		{
		case ELootAbleType::LAT_Weapon:
			MULTICAST_AttachEquip(ActorToAttach, "GunHolder");
			break;
		case ELootAbleType::LAT_Box:
			MULTICAST_AttachEquip(ActorToAttach, "ItemHolder");
			break;
		default:
			break;
		}
	}
}

void ACharacter_Base::DetachActorFromMesh(AActor * ActorToDettach)
{
	if (Role < ROLE_Authority)
	{
		SERVER_DettachEquip(ActorToDettach);
		return;
	}
	MULTICAST_DettachEquip(ActorToDettach);
}

void ACharacter_Base::SetLootableCollision(UStaticMeshComponent * ActorComponentToSet, ECollisionChannel SetChannel, ECollisionResponse ChannelResponse)
{
	if (Role < ROLE_Authority)
	{
		SERVER_SetCollision(ActorComponentToSet, SetChannel, ChannelResponse);
	}
	else 
	{
		MULTICAST_SetCollision(ActorComponentToSet, SetChannel, ChannelResponse);
	}
}

void ACharacter_Base::OnDeathNotifyTimerRespawn()
{
	MyPlayerController->RespawnPlayer();
}

void ACharacter_Base::SERVER_OnPunch_Implementation()
{
	OnPunch();
}

bool ACharacter_Base::SERVER_OnPunch_Validate() 
{
	return true;
}

void ACharacter_Base::MULTICAST_AttachEquip_Implementation(AActor* ActorToAttach, const FName SocketName)
{
	ActorToAttach->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
}

void ACharacter_Base::SERVER_AttachEquip_Implementation(AActor* ActorToAttach)
{
	AttachActorToMesh(ActorToAttach);
}

bool ACharacter_Base::SERVER_AttachEquip_Validate(AActor* ActorToAttach)
{
	return true;
} 

void ACharacter_Base::MULTICAST_SetCollision_Implementation(UStaticMeshComponent * ActorComponentToSet, ECollisionChannel SetChannel, ECollisionResponse ChannelResponse)
{
	if (ActorComponentToSet->IsValidLowLevel())
		ActorComponentToSet->SetCollisionResponseToChannel(SetChannel, ChannelResponse);
}

void ACharacter_Base::SERVER_SetCollision_Implementation(UStaticMeshComponent * ActorComponentToSet, ECollisionChannel SetChannel, ECollisionResponse ChannelResponse)
{
	SetLootableCollision(ActorComponentToSet, SetChannel, ChannelResponse);
}

bool ACharacter_Base::SERVER_SetCollision_Validate(UStaticMeshComponent * ActorComponentToSet, ECollisionChannel SetChannel, ECollisionResponse ChannelResponse)
{
	return true;
}

void ACharacter_Base::SetWeaponVisible(AWeapon_Base* WeaponToHide, bool bShouldHide)
{
	if (Role < ROLE_Authority)
	{
		SERVER_SetWeaponVisible(WeaponToHide, bShouldHide);
	}
	else 
	{
		TArray<UStaticMeshComponent*> StaticMeshComponents;
		WeaponToHide->GetComponents<UStaticMeshComponent>(StaticMeshComponents);
		StaticMeshComponents[0]->SetVisibility(bShouldHide, true);
	}
}

void ACharacter_Base::SERVER_SetWeaponVisible_Implementation(AWeapon_Base* WeaponToHide, bool bShouldHide)
{
	SetWeaponVisible(WeaponToHide, bShouldHide);
}

bool ACharacter_Base::SERVER_SetWeaponVisible_Validate(AWeapon_Base* WeaponToHide, bool bShouldHide)
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

void ACharacter_Base::MULTICAST_DettachEquip_Implementation(AActor * ActorToDettach)
{
	ActorToDettach->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

void ACharacter_Base::FireWeapon()
{
	if (CurrentWeapon->IsValidLowLevel())
		CurrentWeapon->FireWeapon();
}

void ACharacter_Base::SetCurrentWeapon(AWeapon_Base* Weapon)
{
	Inventory.bIsWeaponExist = true;
	if (PreviousWeapon->IsValidLowLevel())
	{
		PreviousWeapon = CurrentWeapon;
	}
	else 
	{
		PreviousWeapon = Weapon;
	}
	CurrentWeapon = Weapon;
}

void ACharacter_Base::OnLootLootable(ACharacter_Base* MyCharacter)
{
	if (Role < ROLE_Authority) 
	{
		SERVER_OnLootLootable(this);
		return;
	}
	MULTICAST_OnLootLootable(MyCharacter);
}

void ACharacter_Base::MULTICAST_OnLootLootable_Implementation(ACharacter_Base* MyCharacter)
{
	ALoot_Base* LootableItem = Cast<ALoot_Base>(GetCurrentSelectedItem().Actor.Get());
	Inventory.PowerUp.Add(LootableItem->GetClass());
	LootableItem->OnPickUp();
}

void ACharacter_Base::SERVER_OnLootLootable_Implementation(ACharacter_Base* MyCharacter)
{
	OnLootLootable(MyCharacter);
}

bool ACharacter_Base::SERVER_OnLootLootable_Validate(ACharacter_Base* MyCharacter)
{
	return true;
}
