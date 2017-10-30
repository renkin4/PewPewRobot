// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyType.h"
#include "Interface/GameplayInterface.h"
#include "HighlightInterface.h"
#include "Loot_Base.generated.h"

UCLASS()
class SEM6_API ALoot_Base : public AActor,
	public IGameplayInterface,
	public IHighlightInterface
{
	GENERATED_UCLASS_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALoot_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void HighLightActor_Implementation() override;
	void TurnOffCustomDepth();
	FTimerHandle TurnOffRenderCustomDepthHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
	FItemToSellInfo LootableInfomation;

	TArray<UStaticMeshComponent*> StaticMeshComp;

public:	
	virtual ELootAbleType GetLootableType_Implementation() override;

	virtual EWeaponType GetWeaponType_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, Category = "PickUp")
	void OnPickUp();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PickUp")
	void OnSpawnAction();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PickUp")
	void OnUseAction();
};
