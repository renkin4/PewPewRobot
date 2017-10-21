// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyType.h"
#include "GameplayInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class UGameplayInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IGameplayInterface
{
	GENERATED_IINTERFACE_BODY()

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameplayInterface", meta = (DisplayName = "GetLootableType"))
	ELootAbleType GetLootableType();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameplayInterface", meta = (DisplayName = "GetWeaponType"))
	EWeaponType GetWeaponType();

};