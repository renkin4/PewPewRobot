// YangIsAwesome

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyType.h"
#include "BoxAIGenerator.generated.h"

class AMyBox;
class ACharacter_Base;

UCLASS()
class SEM6_API ABoxAIGenerator : public AActor
{
	GENERATED_UCLASS_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoxAIGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*Spawn Location*/
	UPROPERTY(EditAnywhere, Category = "Spawn Location")
	TArray<FSpawnLocation> SpawnLocation;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Location")
	TSubclassOf<AMyBox> BoxToSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Location")
	TSubclassOf<ACharacter_Base> AIToSpawn;

	void SpawnBoxOrAI();

	FTimerHandle SpawnHandler;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Location")
	float DelayOnEachSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Location")
	float PercentageToSpawnBox;
	/*-------------------*/

};
