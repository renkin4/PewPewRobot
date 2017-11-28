// YangIsAwesome

#include "Weapon_Base.h"
#include "MyBlueprintFunctionLibrary.h"
#include "DrawDebugHelpers.h"
#include "PlayerController_Base.h"
#include "Projectile_Base.h"
#include "Character_Base.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "HUD_Base.h"
#include "Sem6.h"
#include "EngineUtils.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Components/AudioComponent.h"
#include "SpawnPoint_Base.h"

// Sets default values
AWeapon_Base::AWeapon_Base(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WeaponType = EWeaponType::WT_MachineGun;
	WeaponFireType = EWeaponFireType::WT_InstantHit;
	bReplicates = true;
	bCanFire = true;
	bIsHomming = false;
	bShouldDrawTrajectory = false;
	AdditionalDelay = 0.0f;
	InstantHitSoundCue = CreateDefaultSubobject<UAudioComponent>(TEXT("Instant Hit Audio"));
	InstantHitSoundCue->bAlwaysPlay = false;
	InstantHitSoundCue->SetupAttachment(RootComponent);


	ShowFireLine = false;

}

// Called when the game starts or when spawned
void AWeapon_Base::BeginPlay()
{
	Super::BeginPlay();
	GetComponents<UStaticMeshComponent>(StaticMeshComp);
	StaticMeshComp[0]->CustomDepthStencilValue = 1;
}

// Called every frame
void AWeapon_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon_Base::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AWeapon_Base::HighLightActor_Implementation()
{
	if (StaticMeshComp.IsValidIndex(0)) 
	{
		StaticMeshComp[0]->SetRenderCustomDepth(true);
		GetWorldTimerManager().SetTimer(TurnOffRenderCustomDepthHandle, this, &AWeapon_Base::TurnOffCustomDepth, 0.1f, false);
	}
}

void AWeapon_Base::TurnOffCustomDepth()
{
	StaticMeshComp[0]->SetRenderCustomDepth(false);
}

void AWeapon_Base::ResetCanFire()
{
	bCanFire = true;
}

void AWeapon_Base::DrawPredictTrajectory()
{
	if (!bShouldDrawTrajectory)
		return;

	/*Refactoring these*/
	GetSpawnLocation();
	GetSpawnRotation();
	/*-----------------------*/
	/*Get The Speed and Gravity set in the projectile*/
	const float ProjectileGravity = ProjectileToSpawn->GetDefaultObject<AProjectile_Base>()->GetProjectileGravity();
	const float ProjectileVelocity = ProjectileToSpawn->GetDefaultObject<AProjectile_Base>()->GetInitialProjectileSpeed();
	/*-----------------------*/
	FVector TempLocation = SocketLocation;
	/*Predict Trajectory*/
	FVector CurrentVel = (ProjectileVelocity * UKismetMathLibrary::GetForwardVector(SocketRotation));
	const float GravityZ = GetWorld()->GetDefaultGravityZ()*ProjectileGravity;
	/*Time Variable*/
	float CurrentTime = 0.0f;
	const float MaxSimTime = TrajectoryMaxDrawDuration;
	const float SimFrequency = TrajectoryDrawFrequency;
	const float SubstepDeltaTime = 1.0f / SimFrequency; // The Travel time in 1 Second's Divided by Frequency to get the Amount Segments for 1 Seconds(Basically Draw 20)
	/*-----------------------*/
	/*Start Point And End Points*/
	FVector StartPoint = TempLocation;
	FVector EndPoint = StartPoint;
	/*-----------------------*/
	//Arrays of the Segments
	TArray<FVector> PathSeg;
	PathSeg.Add(TempLocation);

	while (CurrentTime < MaxSimTime)
	{
		/*Find the Segments*/
		const float ActualStepDeltaTime = FMath::Min(MaxSimTime - CurrentTime, SubstepDeltaTime);
		CurrentTime += ActualStepDeltaTime;
		FVector OldVelocity = CurrentVel;
		CurrentVel = OldVelocity + FVector(0.0f, 0.0f, GravityZ * ActualStepDeltaTime);
		StartPoint = EndPoint;
		EndPoint = StartPoint + (OldVelocity + CurrentVel) * (0.5f * ActualStepDeltaTime);
		PathSeg.Add(EndPoint);
	}

	for (int x = 0; x < PathSeg.Num() - 1; x++)
	{
		FRotator PathSegRotation = UKismetMathLibrary::FindLookAtRotation(PathSeg[x], PathSeg[x + 1]);
		FTransform CurrentPathSegTransform = FTransform(PathSegRotation, PathSeg[x]);
		UParticleSystemComponent* TrajectoryPathSegPS;

		PathSegRotation.Yaw = PathSegRotation.Yaw - 90.0f;
		TrajectoryPathSegPS = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TrajectoryShapeParticle, CurrentPathSegTransform, true);
		if (TrajectoryPathSegPS) 
		{
			TrajectoryPathSegPS->SetWorldRotation(PathSegRotation);
			TrajectoryPathSegPSArray.Add(TrajectoryPathSegPS);
		}
		
		
		
		//TrajectoryParticle->SetBeamTargetPoint(0, PathSeg[x + 1],0);
		//DrawDebugLine(GetWorld(), PathSeg[x], PathSeg[x + 1], FColor::Purple, false, 0.05f, 0, 0.5f);
	}

	/*-----------------------------------------------------------*/
}

void AWeapon_Base::FlushTrajectoryProjectile()
{
	for (UParticleSystemComponent* PSC : TrajectoryPathSegPSArray) 
	{
		PSC->DestroyComponent();
	}
	TrajectoryPathSegPSArray.Empty();
}

void AWeapon_Base::HommingMissleTargetTrace_Implementation()
{
	FHitResult HitData(ForceInit);
	APlayerController_Base* PlayerOwner = Cast<APlayerController_Base>(PawnOwner);
	FVector WorldPosition;
	FVector WorldDirection;
	const int32 TraceDistance = 7000;
	const float SphereRadius = 200.0f;

	if (PlayerOwner)
	{
		FCollisionQueryParams TraceParams(FName(TEXT("Missle Trace")), true, PlayerOwner->GetPawn());
		TraceParams.bTraceComplex = false;
		TraceParams.bReturnPhysicalMaterial = false;
		TraceParams.AddIgnoredActor(this);
		TraceParams.AddIgnoredActor(PlayerOwner->GetPawn());

		PlayerOwner->DeprojectScreenPositionToWorld(GetScreenLocation().X*0.5f, GetScreenLocation().Y*0.5f, WorldPosition, WorldDirection);
		FVector StartPoint = WorldPosition;
		FVector EndPoint = StartPoint + (WorldDirection * TraceDistance);
		GetWorld()->SweepSingleByChannel(HitData, StartPoint, EndPoint, FQuat(), ECollisionChannel::ECC_GameTraceChannel6, FCollisionShape::MakeSphere(SphereRadius), TraceParams);
		if (HitData.bBlockingHit) 
		{
			if (HitData.Actor->GetClass()->IsChildOf(ACharacter_Base::StaticClass())) 
			{
				AHUD_Base* MyHUD = Cast<AHUD_Base>(PlayerOwner->GetHUD());
				if (MyHUD) 
				{
					MyHUD->SetHommingTargetted(true);
					MyHUD->SetHommingTargetLocation(HitData.Actor->GetActorLocation());
					HommingTarget = HitData.GetActor();
					GetWorldTimerManager().SetTimer(ResetHomingLauncherHandle, this, &AWeapon_Base::ResetHomingLauncher, 0.5f, false);
				}
			}
				
		}
	}
	//APlayerController_Base* PlayerOwner = Cast<APlayerController_Base>(PawnOwner);
	//FVector WorldPosition;
	//FVector WorldDirection;

	//if (PlayerOwner)
	//{
	//	
	//}
}

void AWeapon_Base::ResetHomingLauncher()
{
	APlayerController_Base* PlayerOwner = Cast<APlayerController_Base>(PawnOwner);
	AHUD_Base* MyHUD = Cast<AHUD_Base>(PlayerOwner->GetHUD());
	if (PlayerOwner) 
	{
		if (MyHUD)
		{
			MyHUD->SetHommingTargetted(false);
			HommingTarget = NULL;
		}
	}
}

void AWeapon_Base::OnBeginOverlapComponentForLockOn(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerController_Base* PlayerOwner = Cast<APlayerController_Base>(PawnOwner);
	if (PlayerOwner)
	{
		if (OtherActor == this || OtherActor == PlayerOwner->GetPawn() || OtherActor->GetClass()->IsChildOf(ASpawnPoint_Base::StaticClass()))
			return;
		
		AHUD_Base* MyHUD = Cast<AHUD_Base>(PlayerOwner->GetHUD());
		if (MyHUD)
		{
			MyHUD->SetHommingTargetted(true);
			MyHUD->SetHommingTargetLocation(OtherActor->GetActorLocation());
			HommingTarget = OtherActor;
			GetWorldTimerManager().SetTimer(ResetHomingLauncherHandle, this, &AWeapon_Base::ResetHomingLauncher, 0.5f, false);
		}
	}
	
}

ELootAbleType AWeapon_Base::GetLootableType_Implementation()
{
	return LootableType;
}

EWeaponType AWeapon_Base::GetWeaponType_Implementation()
{
	return WeaponType;
}

void AWeapon_Base::FireWeapon()
{
	if (!CanFire())
		return;

	ACharacter_Base* CharOwner = Cast<ACharacter_Base>(PawnOwner->GetPawn());
	if (CharOwner) 
	{
		if (CharOwner->GetStaminaVal() >= GetStaminaCost())
		{
			CharOwner->SetStamina(CharOwner->GetStaminaVal() - MyStats.StaminaCost, true);
			FilterFireType();
		}
		else
		{
			CharOwner->StopFiring();
		//	CharOwner->OnChangeWeapon(); // Get Animation Reset
		}
	}
	//TODO Simulate Particle and sound
	//TODO Set EditAnywhere for Particle And sound
}

void AWeapon_Base::SetPawnOwner(AController* Controller)
{
	PawnOwner = Controller;
	return;
}

void AWeapon_Base::DrawTrajectory()
{
	if (TrajectoryPathSegPSArray.Num() > 0)
		FlushTrajectoryProjectile();

	DrawPredictTrajectory();

	GetWorldTimerManager().SetTimer(ResetTrajectory, this, &AWeapon_Base::FlushTrajectoryProjectile, 0.1f, false);
}

FVector2D AWeapon_Base::GetScreenLocation()
{
	APlayerController_Base* PlayerOwner = Cast<APlayerController_Base>(PawnOwner);
	int32 ViewportY;
	int32 ViewportX;

	if (PlayerOwner) 
	{
		PlayerOwner->GetViewportSize(ViewportX, ViewportY);
		return FVector2D(ViewportX, ViewportY);
	}
	return FVector2D(0.0f, 0.0f);
}

void AWeapon_Base::FilterFireType()
{
	switch (WeaponFireType)
	{
	case EWeaponFireType::WT_None:
		break;
	case EWeaponFireType::WT_ProjecTile:
		if (CanFire()) 
		{
			SpawnProjectile();
			bCanFire = false;
			GetWorldTimerManager().SetTimer(SpawnFireCoolDown, this, &AWeapon_Base::ResetCanFire, GetWeaponDelay(), true);
		}
		break;
	case EWeaponFireType::WT_InstantHit:
		InstantHitSoundCue->Play();
		InstantHitFire();
		break;
	default:
		break;
	}
}

void AWeapon_Base::InstantHitFire()
{
	FHitResult HitScreenData(ForceInit);
	FHitResult HitData(ForceInit);
	FHitResult DamageInfo(ForceInit);
	APlayerController_Base* PlayerOwner = Cast<APlayerController_Base>(PawnOwner);
	FVector WorldPosition;
	FVector WorldDirection;
	if (PlayerOwner)
	{
		PlayerOwner->DeprojectScreenPositionToWorld(GetScreenLocation().X*0.5f, GetScreenLocation().Y*0.5f, WorldPosition, WorldDirection);
		FVector StartPoint;
		FVector EndPoint;

		if (PlayerOwner->GetIsAiming())
		{
			StartPoint = WorldPosition;
			EndPoint = WorldPosition + (WorldDirection * 5000);
			FVector ShootStartPoint = StaticMeshComp[0]->GetSocketLocation("ShootingPoint");
			FVector ShootEndPoint;
			UMyBlueprintFunctionLibrary::Trace(GetWorld(), this, StartPoint, EndPoint, HitScreenData, ECC_Visibility, false);

			ShootEndPoint = HitScreenData.bBlockingHit ? HitScreenData.ImpactPoint : WorldPosition + (WorldDirection * 5000);
			//SIMULATE FX
			PlayerOwner->SimulateParticleFX(MuzzleParticle,FTransform(StaticMeshComp[0]->GetSocketRotation("ShootingPoint"),FVector(ShootStartPoint)),true);
			//Trace From Gun
			if (UMyBlueprintFunctionLibrary::Trace(GetWorld(), this, ShootStartPoint, ShootEndPoint, HitData, ECC_Visibility, false))
			{
				PlayerOwner->DealDamage(HitData.Actor.Get(), 1.0f, HitData.ImpactNormal, DamageInfo, PawnOwner, this, InstantShotDamageType);
				PlayerOwner->SimulateParticleFX(HitParticle, FTransform(GetActorRotation(), FVector(HitData.ImpactPoint)), true);

				//UGameplayStatics::ApplyPointDamage(HitData.Actor.Get(), 1.0f, HitData.ImpactNormal, DamageInfo, PawnOwner, this, InstantShotDamageType);
				////stun player
				//ACharacter_Base* AffectedCharacter = Cast<ACharacter_Base>(HitData.Actor.Get());
				//if (AffectedCharacter)
				//	AffectedCharacter->StunPlayer(MyStats.StunDelayDuration);

				/*Debug*/
				//TODO refactor to Debug Line Function
				DrawDebugSolidBox(GetWorld(), ShootEndPoint, FVector(10.0f, 10.0f, 5.0f), FColor::Red, false, 0.5f, 0);
			}
			/*Debug*/
			DebugLine(ShootStartPoint, ShootEndPoint, FColor::Green);
		}
		else
		{
			StartPoint = StaticMeshComp[0]->GetSocketLocation("ShootingPoint");
			EndPoint = StaticMeshComp[0]->GetSocketLocation("ShootingPoint") + (2000 * UKismetMathLibrary::GetForwardVector(StaticMeshComp[0]->GetSocketRotation("ShootingPoint")));
			//SIMULATE FX
			PlayerOwner->SimulateParticleFX(MuzzleParticle, FTransform(StaticMeshComp[0]->GetSocketRotation("ShootingPoint"), FVector(StartPoint)), true);

			//Without Aiming
			if (UMyBlueprintFunctionLibrary::Trace(GetWorld(), this, StartPoint, EndPoint, HitData, ECC_Visibility, false))
			{
				//UGameplayStatics::ApplyPointDamage(HitData.Actor.Get(), 1.0f, HitData.ImpactNormal, DamageInfo, PawnOwner, this, InstantShotDamageType);
				PlayerOwner->DealDamage(HitData.Actor.Get(), 1.0f, HitData.ImpactNormal, DamageInfo, PawnOwner, this, InstantShotDamageType);
				PlayerOwner->SimulateParticleFX(HitParticle, FTransform(StaticMeshComp[0]->GetSocketRotation("ShootingPoint"), FVector(HitData.ImpactPoint)), true);
				////stun player
				//ACharacter_Base* AffectedCharacter = Cast<ACharacter_Base>(HitData.Actor.Get());
				//if (AffectedCharacter)
				//	AffectedCharacter->StunPlayer(MyStats.StunDelayDuration);

				EndPoint = HitData.ImpactPoint;
				DrawDebugSolidBox(GetWorld(), EndPoint, FVector(10.0f, 10.0f, 5.0f), FColor::Red, false, 0.5f, 0);
			}
			/*Debug*/
			DebugLine(StartPoint, EndPoint, FColor::Green);
		}
	}
}

void AWeapon_Base::SpawnProjectile()
{
	if (!CanFire())
		return;

	APlayerController_Base* PlayerOwner = Cast<APlayerController_Base>(PawnOwner);
	FVector WorldPosition;
	FVector WorldDirection;
	SocketLocation = StaticMeshComp[0]->GetSocketLocation("SpawnProjectileLocation");

	if (PlayerOwner)
	{
		PlayerOwner->SimulateParticleFX(MuzzleParticle, FTransform(
			UKismetMathLibrary::InvertTransform(FTransform(StaticMeshComp[0]->GetSocketRotation("SpawnProjectileLocation"),FVector(0.f))).GetRotation(),
			FVector(SocketLocation)),
			true);

		if (PlayerOwner->GetIsAiming())
		{
			PlayerOwner->DeprojectScreenPositionToWorld(GetScreenLocation().X*0.5f, GetScreenLocation().Y*0.5f, WorldPosition, WorldDirection);
			FVector EndPoint = WorldPosition + (WorldDirection * 5000);
			SocketRotation = UKismetMathLibrary::FindLookAtRotation(PlayerOwner->GetPawn()->GetActorLocation(), EndPoint);
			FVector TempLocation = SocketLocation;

		}
		else
		{
			SocketRotation = StaticMeshComp[0]->GetSocketRotation("SpawnProjectileLocation");;
		}
		AActor* ProjectileSpawned = PlayerOwner->SpawnProjectile(SocketLocation, SocketRotation, ProjectileToSpawn, this, HommingTarget);
	}
}

void AWeapon_Base::GetSpawnLocation()
{
	SocketLocation = StaticMeshComp[0]->GetSocketLocation("SpawnProjectileLocation");
}

void AWeapon_Base::GetSpawnRotation()
{
	APlayerController_Base* PlayerOwner = Cast<APlayerController_Base>(PawnOwner);
	FVector WorldPosition;
	FVector WorldDirection;

	if (PlayerOwner)
	{
		if (PlayerOwner->GetIsAiming())
		{
			PlayerOwner->DeprojectScreenPositionToWorld(GetScreenLocation().X*0.5f, GetScreenLocation().Y*0.5f, WorldPosition, WorldDirection);
			FVector EndPoint = WorldPosition + (WorldDirection * 5000);
			SocketRotation = UKismetMathLibrary::FindLookAtRotation(PlayerOwner->GetPawn()->GetActorLocation(), EndPoint);
			FVector TempLocation = SocketLocation;
			
		}
		else
		{
			SocketRotation = StaticMeshComp[0]->GetSocketRotation("SpawnProjectileLocation");;
		}
	}
}

void AWeapon_Base::DebugLine(FVector Start, FVector End, FColor Color)
{
	//TODO set enum and check from Bool
	if (ShowFireLine) 
	{
		DrawDebugLine(GetWorld(), Start, End, Color, false, 1.0f, 0, 1.0f);
	}
}

