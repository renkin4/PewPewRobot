// Fill out your copyright notice in the Description page of Project Settings.

#include "Interface/GameplayInterface.h"

UGameplayInterface::UGameplayInterface(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

ELootAbleType IGameplayInterface::GetLootableType_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CRITICAL ERROR: No GameplayInterface found on GetLootableItem"));
	return ELootAbleType::LAT_None;
}

EWeaponType IGameplayInterface::GetWeaponType_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CRITICAL ERROR: No GameplayInterface found on GetWeapon"));
	return EWeaponType::WT_None;
}

