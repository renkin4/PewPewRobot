// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUD_Base.generated.h"

/**
 * 
 */
UCLASS()
class SEM6_API AHUD_Base : public AHUD
{
	GENERATED_UCLASS_BODY()
protected:
	virtual void BeginPlay() override;

	virtual void DrawHUD() override;

	FVector HommingTargetLocation;

	//remember to SetHomminglocation on Targetted;
	bool bHommingTargetted;

	UFUNCTION(BlueprintNativeEvent, Category = "Draw Hud")
	void StartPulse();

public:
	void DrawHommingTarget(FVector Location);

	UPROPERTY(BlueprintReadWrite, Category = "Draw Hud")
	float Pulse;

	void SetHommingTargetted(bool bShouldSetHommingTargetted) { bHommingTargetted = bShouldSetHommingTargetted; }

	void SetHommingTargetLocation(FVector NewLocation) { HommingTargetLocation = NewLocation; }
};
