// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MyGameState_Base.generated.h"

class APlayerState_Base;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnJoinTeam, APlayerState_Base*, PS, uint8, TeamNum);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLeaveTeam, uint8, TeamNum);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateEveryoneReadyStatus, APlayerState_Base*, PS);


UCLASS()
class SEM6_API AMyGameState_Base : public AGameState
{
	GENERATED_UCLASS_BODY()
public:

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
	/*Lobby*/

	UFUNCTION(BlueprintCallable, Category = "Lobby")
	void OnJoinTeam(APlayerState_Base* PS, uint8 TeamToJoin);

	UFUNCTION(BlueprintCallable, Category = "Lobby")
	bool UpdateReadyStatus(APlayerState_Base* PS);

	UFUNCTION(BlueprintCallable, Category = "Lobby")
	void OnLeaveTeam(uint8 TeamNum);

	UFUNCTION(BlueprintPure, Category = "Lobby")
	bool CheckEveryoneReady(APlayerState_Base* ServerPS);
	/*---------------------------------------------------*/
	
protected:
	virtual void HandleMatchHasStarted() override;

	/*Score*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Score")
	void OnWin(APlayerState_Base* PState);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	float WiningScore;
	/*----------------------------------------------------*/
	/*Lobby*/
	UFUNCTION(NetMultiCast, Reliable)
	void MULTICAST_OnJoinTeam(APlayerState_Base* PS, uint8 TeamToJoin);


	UFUNCTION(NetMultiCast, Reliable)
	void MULTICAST_OnLeaveTeam(uint8 TeamNum);

	UFUNCTION(NetMultiCast, Reliable)
	void MULTICAST_UpdateReadyStatus(APlayerState_Base* PS);

	UPROPERTY(BlueprintAssignable)
	FOnJoinTeam DelegateJoinTeam;

	UPROPERTY(BlueprintAssignable)
	FOnLeaveTeam DelegateLeaveTeam;

	UPROPERTY(BlueprintAssignable)
	FUpdateEveryoneReadyStatus UpdateRSDelegate;
	/*----------------------------------------------------*/

	
};
