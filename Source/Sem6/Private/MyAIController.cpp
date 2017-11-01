// YangIsAwesome

#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "PlayerState_Base.h"
#include "MyGameState_Base.h"
#include "Weapon_Base.h"
#include "AICharacter.h"
#include "Engine.h"


AMyAIController::AMyAIController(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	BlackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComp"));

	BrainComponent = BehaviorComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));

	bIsStunned = false;
	PrimaryActorTick.bCanEverTick = false;

	//bWantsPlayerState = true;
}

void AMyAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	AAICharacter* Bot = Cast<AAICharacter>(InPawn);

	// start behavior
	if (Bot && Bot->BotBehavior)
	{
		if (Bot->BotBehavior->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*Bot->BotBehavior->BlackboardAsset);
		}

		EnemyKeyID = BlackboardComp->GetKeyID("Enemy");
		IsStunnedID = BlackboardComp->GetKeyID("bIsStunned");
		LastKnownLocationID = BlackboardComp->GetKeyID("LastKnownLocation");
		bLostSightID = BlackboardComp->GetKeyID("bLostSight");

		BehaviorComp->StartTree(*(Bot->BotBehavior));
	}
}

void AMyAIController::UnPossess()
{
	Super::UnPossess();

	BehaviorComp->StopTree();
}

void AMyAIController::BeginInactiveState()
{
	Super::BeginInactiveState();

	AGameStateBase const* const GameState = GetWorld()->GetGameState();

	const float MinRespawnDelay = GameState ? GameState->GetPlayerRespawnDelay(this) : 1.0f;

	//TODO Spawn Character from MYgamemode Respawn Delay
	//GetWorldTimerManager().SetTimer(TimerHandle_Respawn, this, &AMyAIController::Respawn, MinRespawnDelay);
}

void AMyAIController::Respawn()
{
	GetWorld()->GetAuthGameMode()->RestartPlayer(this);
}

void AMyAIController::FindClosestEnemy_Implementation()
{
	APawn* MyBot = GetPawn();
	if (MyBot == NULL)
	{
		return;
	}

	const FVector MyLoc = MyBot->GetActorLocation();
	float BestDistSq = MAX_FLT;
	ACharacter_Base* BestPawn = NULL;

	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	{

		ACharacter_Base* TestPawn = Cast<ACharacter_Base>(*It);
		if (TestPawn && TestPawn->IsAlive() && TestPawn->IsEnemyFor(this))
		{
			const float DistSq = (TestPawn->GetActorLocation() - MyLoc).SizeSquared();
			if (DistSq < BestDistSq)
			{
				BestDistSq = DistSq;
				BestPawn = TestPawn;
			}
		}
	}

	if (BestPawn)
	{
		SetEnemy(BestPawn);
	}
}

bool AMyAIController::FindClosestEnemyWithLOS_Implementation(ACharacter_Base* ExcludeEnemy)
{
	bool bGotEnemy = false;
	APawn* MyBot = GetPawn();

	if (MyBot != NULL)
	{
		const FVector MyLoc = MyBot->GetActorLocation();
		float BestDistSq = MAX_FLT;
		ACharacter_Base* BestPawn = NULL;

		for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
		{
			ACharacter_Base* TestPawn = Cast<ACharacter_Base>(*It);

			if (TestPawn && TestPawn != ExcludeEnemy && TestPawn->IsAlive() && TestPawn->IsEnemyFor(this))
			{
				
				if (HasWeaponLOSToEnemy(TestPawn, true) == true)
				{
					const float DistSq = (TestPawn->GetActorLocation() - MyLoc).SizeSquared();
					if (DistSq < BestDistSq)
					{
						BestDistSq = DistSq;
						BestPawn = TestPawn;
						
					}
				}
				else 
				{
					BestPawn = NULL;
				}
			}
		}
		if (BestPawn)
		{
			if (BestPawn) 
				SetLastKnownLocation(BestPawn->GetActorLocation());
			SetEnemy(BestPawn);
			bGotEnemy = true;
		}
		else 
		{
			SetEnemy(NULL);
			bGotEnemy = false;
		}
	}
	return bGotEnemy;
}

void AMyAIController::SetEnemy(class APawn* InPawn)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValue<UBlackboardKeyType_Object>(EnemyKeyID, InPawn);
		SetFocus(InPawn);
	}
}

void AMyAIController::SetLastKnownLocation(const FVector & LastKnownLocation)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValue<UBlackboardKeyType_Bool>(bLostSightID, true);
		BlackboardComp->SetValue<UBlackboardKeyType_Vector>(LastKnownLocationID,LastKnownLocation);
	}
}

bool AMyAIController::HasWeaponLOSToEnemy(AActor* InEnemyActor, const bool bAnyEnemy) 
{
	static FName LosTag = FName(TEXT("AIWeaponLosTrace"));

	AAICharacter* MyBot = Cast<AAICharacter>(GetPawn());

	bHasLOS = false;
	//// Perform trace to retrieve hit info
	FCollisionQueryParams TraceParams(LosTag, true, GetPawn());
	TraceParams.bTraceAsyncScene = true;

	TraceParams.bReturnPhysicalMaterial = true;
	FVector StartLocation = MyBot->GetActorLocation();
	StartLocation.Z += GetPawn()->BaseEyeHeight; //look from eyes
	FHitResult Hit(ForceInit);
	const FVector EndLocation = InEnemyActor->GetActorLocation();
	//Find the Look at Angle
	float Dot = FVector::DotProduct(
		UKismetMathLibrary::GetForwardVector(GetPawn()->GetActorRotation()),
		UKismetMathLibrary::GetForwardVector(UKismetMathLibrary::FindLookAtRotation(StartLocation, EndLocation))
		);
	//Check for distance And Angle
	if ((StartLocation - EndLocation).SizeSquared() > LineOfSightRangeSq || Dot < DotProductRange)
	{
		return false;
	}
	GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Visibility, TraceParams);

	if (Hit.bBlockingHit == true)
	{
		// Theres a blocking hit - check if its our enemy actor
		AActor* HitActor = Hit.GetActor();
		if (Hit.GetActor() != NULL)
		{
			if (HitActor == InEnemyActor)
			{
				bHasLOS = true;
			}
			else if (bAnyEnemy == true)
			{
				// Its not our actor, maybe its still an enemy ?
				ACharacter* HitChar = Cast<ACharacter>(HitActor);
				if (HitChar != NULL)
				{
					APlayerState_Base* HitPlayerState = Cast<APlayerState_Base>(HitChar->PlayerState);
					APlayerState_Base* MyPlayerState = Cast<APlayerState_Base>(PlayerState);
					if ((HitPlayerState != NULL) && (MyPlayerState != NULL))
					{
						if (HitPlayerState->GetTeamNum() != MyPlayerState->GetTeamNum())
						{
							bHasLOS = true;
						}
					}
				}
			}
		}
	}
	
	return bHasLOS;
}

void AMyAIController::ShootEnemy_Implementation()
{
	AAICharacter* MyBot = Cast<AAICharacter>(GetPawn());
	/*AWeapon_Base* MyWeapon = MyBot ? MyBot->GetWeapon() : NULL;
	if (MyWeapon == NULL)
	{
		return;
	}
*/
	bool bCanShoot = false;

	/*ACharacter_Base* Enemy = GetEnemy();
	if (Enemy && (Enemy->IsAlive()) && (MyWeapon->GetCurrentAmmo() > 0) && (MyWeapon->CanFire() == true))
	{
		if (LineOfSightTo(Enemy, MyBot->GetActorLocation()))
		{
			bCanShoot = true;
		}
	}

	if (bCanShoot)
	{
		MyBot->StartWeaponFire();
	}
	else
	{
		MyBot->StopWeaponFire();
	}*/

	/*Temp*/
	static FName LosTag = FName(TEXT("ShootEnemyTemp"));
	ACharacter_Base* Enemy = GetEnemy();
	//// Perform trace to retrieve hit info
	FCollisionQueryParams TraceParams(LosTag, true, GetPawn());
	TraceParams.bTraceAsyncScene = true;

	TraceParams.bReturnPhysicalMaterial = true;
	FVector StartLocation = MyBot->GetActorLocation();
	StartLocation.Z += GetPawn()->BaseEyeHeight; //look from eyes

	FHitResult Hit(ForceInit);
	FHitResult DamageInfo(ForceInit);
	const FVector EndLocation = GetPawn()->GetActorLocation() + (GetActorForwardVector() * 2000);
	GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_GameTraceChannel5, TraceParams);
	DrawDebugLine(GetWorld(),StartLocation,EndLocation,FColor::Red, false, 0.5f, 0, 10.0f);
	if (Hit.bBlockingHit)
	{
		bCanShoot = true;

	}
	if (bCanShoot)
	{
		//TEMP TEMP TEMP SHOOT FROM WEAPON
		UGameplayStatics::ApplyPointDamage(Hit.Actor.Get(), 1.0f, Hit.ImpactNormal, DamageInfo,this,GetPawn(), InstantShotDamageType);

		//TODO Start Fire Weapon if weapon exist
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("Shoot if weapon Exist"));
	}
	//

}

class ACharacter_Base* AMyAIController::GetEnemy() const
{
	if (BlackboardComp)
	{
		return Cast<ACharacter_Base>(BlackboardComp->GetValue<UBlackboardKeyType_Object>(EnemyKeyID));
	}

	return NULL;
}

void AMyAIController::UpdateControlRotation(float DeltaTime, bool bUpdatePawn)
{
	// Look toward focus
	FVector FocalPoint = GetFocalPoint();
	if (!FocalPoint.IsZero() && GetPawn())
	{
		FVector Direction = FocalPoint - GetPawn()->GetActorLocation();
		FRotator NewControlRotation = Direction.Rotation();

		NewControlRotation.Yaw = FRotator::ClampAxis(NewControlRotation.Yaw);

		SetControlRotation(NewControlRotation);

		APawn* const P = GetPawn();
		if (P && bUpdatePawn)
		{
			P->FaceRotation(NewControlRotation, DeltaTime);
		}

	}
}

void AMyAIController::SetStunAI_Implementation(bool bShouldStun, float StunnedDelay)
{
	bIsStunned = bShouldStun;
	if (BlackboardComp)
	{
		BlackboardComp->SetValue<UBlackboardKeyType_Bool>(IsStunnedID, bShouldStun);
		BlackboardComp->SetValueAsFloat("StunnedTimer", StunnedDelay);
	}
}

void AMyAIController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	// Stop the behaviour tree/logic
	BehaviorComp->StopTree();

	// Stop any movement we already have
	StopMovement();

	// Cancel the repsawn timer
	GetWorldTimerManager().ClearTimer(TimerHandle_Respawn);

	// Clear any enemy
	SetEnemy(NULL);

	// Finally stop firing
	AAICharacter* MyBot = Cast<AAICharacter>(GetPawn());
	//TODO Check for weapon and stop firing if that's the case
	//AWeapon_Base* MyWeapon = MyBot ? MyBot->GetWeapon() : NULL;
	/*if (MyWeapon == NULL)
	{
		return;
	}*/
	//MyBot->StopWeaponFire();
}