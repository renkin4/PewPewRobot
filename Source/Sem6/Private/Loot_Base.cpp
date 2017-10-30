// Fill out your copyright notice in the Description page of Project Settings.

#include "Loot_Base.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ALoot_Base::ALoot_Base(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

}

void ALoot_Base::BeginPlay()
{
	Super::BeginPlay();
	GetComponents<UStaticMeshComponent>(StaticMeshComp);
	StaticMeshComp[0]->CustomDepthStencilValue = 1;
}

void ALoot_Base::HighLightActor_Implementation()
{
	if (StaticMeshComp.IsValidIndex(0))
	{
		StaticMeshComp[0]->SetRenderCustomDepth(true);
		GetWorldTimerManager().SetTimer(TurnOffRenderCustomDepthHandle, this, &ALoot_Base::TurnOffCustomDepth, 0.1f, false);
	}
}

void ALoot_Base::TurnOffCustomDepth()
{
	StaticMeshComp[0]->SetRenderCustomDepth(false);
}

ELootAbleType ALoot_Base::GetLootableType_Implementation()
{
	return ELootAbleType::LAT_PowerUp;
}

EWeaponType ALoot_Base::GetWeaponType_Implementation()
{
	return EWeaponType::WT_None;
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

