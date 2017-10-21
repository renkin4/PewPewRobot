// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MyGameState_Base.generated.h"

class APlayerState_Base;
/**
 * 
 */
UCLASS()
class SEM6_API AMyGameState_Base : public AGameState
{
	GENERATED_UCLASS_BODY()
public:
	/*Sound Deprecating this soon*/
	UFUNCTION(NetMultiCast, Reliable, BlueprintCallable, Category = "Sound")
	void MULTICAST_PlaySoundAtLocation(USoundBase * Sound, FVector Location, float VolumeMultiplier, float PitchMultiplier, float StartTime, class USoundAttenuation * AttenuationSettings, USoundConcurrency * ConcurrencySettings);
	/*----------------------------------------------------*/

	/*Score*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Score")
	void CheckScore();
	/*----------------------------------------------------*/
	/*DestroyActor*/
	UFUNCTION(NetMultiCast, Reliable, BlueprintCallable, Category = "Actor")
	void MULTICAST_DestroyActor(AActor* ActorToDestroy);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Actor")
	void DestroyingActor(AActor* ActorToDestroy);
	/*----------------------------------------------------*/
protected:
	/*Score*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Score")
	void OnWin(APlayerState_Base* PState);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	float WiningScore;
	/*----------------------------------------------------*/

	
};
