// YangIsAwesome

#include "BoxAIGenerator.h"
#include "Character_Base.h"
#include "MyBox.h"
#include "MyGameMode_Base.h"
#include "Kismet/GameplayStatics.h"
#include "Sem6.h"


// Sets default values
ABoxAIGenerator::ABoxAIGenerator(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	DelayOnEachSpawn = 30.0f;
	PercentageToSpawnBox = 0.75f;
	bAlwaysRelevant = true;
}

// Called when the game starts or when spawned
void ABoxAIGenerator::BeginPlay()
{
	Super::BeginPlay();
	SpawnBoxOrAI();
	GetWorldTimerManager().SetTimer(SpawnHandler, this, &ABoxAIGenerator::SpawnBoxOrAI, DelayOnEachSpawn, true);
}

void ABoxAIGenerator::SpawnBoxOrAI()
{
	UWorld* World = GetWorld();
	AMyGameMode_Base* GM = Cast<AMyGameMode_Base>(World->GetAuthGameMode());
	if (GM) 
	{
		//for (auto SL : SpawnLocation)
		//{
		//	float RandNum = FMath::FRand();
		//	if (!SL.MyActor->IsValidLowLevel())
		//	{
		//		if (RandNum < 0.75f) 
		//			SL.MyActor = GM->SpawnBox(BoxToSpawn, GetActorLocation() + SL.MyLocation);
		//		else
		//			SL.MyActor = GM->SpawnCharacter(AIToSpawn, GetActorLocation() + SL.MyLocation);
		//	}
		//}

		GetWorld()->ForceGarbageCollection(true); //full purge 

		for (int x = 0; x < SpawnLocation.Num(); x++) 
		{
			float RandNum = FMath::FRand();
			if (!SpawnLocation[x].MyActor->IsValidLowLevel())
			{
				if (RandNum < PercentageToSpawnBox)
					SpawnLocation[x].MyActor = GM->SpawnBox(BoxToSpawn, GetActorLocation() + SpawnLocation[x].MyLocation);
				else
					SpawnLocation[x].MyActor = GM->SpawnCharacter(AIToSpawn, GetActorLocation() + SpawnLocation[x].MyLocation);
			}
		}
	}
}

