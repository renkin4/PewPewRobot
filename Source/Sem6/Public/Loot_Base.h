// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/GameplayInterface.h"
#include "MyType.h"
#include "GameFramework/Actor.h"
#include "Loot_Base.generated.h"

UCLASS()
class SEM6_API ALoot_Base : public AActor,
	public IGameplayInterface
{
	GENERATED_UCLASS_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALoot_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
	FLootableStruct LootableInfomation;

public:	
	virtual ELootAbleType GetLootableType_Implementation() override;

	virtual EWeaponType GetWeaponType_Implementation() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, Category = "PickUp")
	void OnPickUp();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PickUp")
	void OnSpawnAction();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PickUp")
	void OnUseAction();
};
