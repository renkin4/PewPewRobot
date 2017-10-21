// Fill out your copyright notice in the Description page of Project Settings.

#include "Loot_Base.h"


// Sets default values
ALoot_Base::ALoot_Base(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

}

void ALoot_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

ELootAbleType ALoot_Base::GetLootableType_Implementation()
{
	return ELootAbleType::LAT_PowerUp;
}

EWeaponType ALoot_Base::GetWeaponType_Implementation()
{
	return EWeaponType::WT_None;
}

// Called every frame
void ALoot_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALoot_Base::OnUseAction_Implementation()
{
}

void ALoot_Base::OnSpawnAction_Implementation()
{
}

void ALoot_Base::OnPickUp_Implementation()
{
	if (!this->IsPendingKill()) 
	{
		this->Destroy();
	}
	return;
}

