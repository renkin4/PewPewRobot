// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerState_Base.generated.h"

class ASpawnPoint_Base;
class MyPlayerStart_Base;

/**
 * 
 */
UCLASS()
class SEM6_API APlayerState_Base : public APlayerState
{
	GENERATED_UCLASS_BODY()
public:
	/** PlayerStart Ref */
	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void SetPlayerStartLocation(APlayerStart* LocationToSet);

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void SetSpawnLocation(ASpawnPoint_Base* LocationToSet);

	UFUNCTION(BlueprintPure, Category = "Spawn")
	ASpawnPoint_Base* GetSpawnLocation();

	UFUNCTION(BlueprintPure, Category = "Spawn")
	APlayerStart* GetPlayerStartLocation();

	// Begin APlayerState interface
	/** clear scores */
	virtual void Reset() override;

	/**
	* Set the team
	*
	* @param	InController	The controller to initialize state with
	*/
	virtual void ClientInitialize(class AController* InController) override;

	virtual void UnregisterPlayerWithSession() override;

	// End APlayerState interface

	/**
	* Set new team and update pawn. Also updates player character team colors.
	*
	* @param	NewTeamNumber	Team we want to be on.
	*/
	UFUNCTION(BlueprintCallable, Category = "Team")
	void SetTeamNum(uint8 NewTeamNumber);

	/** player killed someone */
	void ScoreKill(APlayerState_Base* Victim, int32 Points);

	/** player died */
	void ScoreDeath(APlayerState_Base* KilledBy, int32 Points);

	/** get current team */
	UFUNCTION(BlueprintPure, Category = "Team")
	uint8 GetTeamNum() const;

	/** get number of kills */
	int32 GetKills() const;

	/** get number of deaths */
	int32 GetDeaths() const;

	/** get number of points */
	float GetScore() const;

	/** get number of bullets fired this match */
	int32 GetNumBulletsFired() const;

	/** get number of rockets fired this match */
	int32 GetNumRocketsFired() const;

	/** get whether the player quit the match */
	bool IsQuitter() const;

	/** gets truncated player name to fit in death log and scoreboards */
	FString GetShortPlayerName() const;

	/** Sends kill (excluding self) to clients */
	UFUNCTION(Reliable, Client)
	void InformAboutKill(class APlayerState_Base* KillerPlayerState, const UDamageType* KillerDamageType, class APlayerState_Base* KilledPlayerState);

	/** broadcast death to local clients */
	UFUNCTION(Reliable, NetMulticast)
	void BroadcastDeath(class APlayerState_Base* KillerPlayerState, const UDamageType* KillerDamageType, class APlayerState_Base* KilledPlayerState);

	/** replicate team colors. Updated the players mesh colors appropriately */
	UFUNCTION()
	void OnRep_TeamColor();

	//We don't need stats about amount of ammo fired to be server authenticated, so just increment these with local functions
	void AddBulletsFired(int32 NumBullets);
	void AddRocketsFired(int32 NumRockets);

	/** Set whether the player is a quitter */
	void SetQuitter(bool bInQuitter);

	virtual void CopyProperties(class APlayerState* PlayerState) override;

	UFUNCTION(Client,Reliable)
	void CLIENT_UpdateColorOfSpawn(UStaticMeshComponent* MeshToChangeColor, UMaterialInterface* MaterialChangeTo);

	UFUNCTION(BlueprintPure, Category = "Controller")
	APlayerController_Base* GetMyController();

	UFUNCTION(BlueprintCallable, Category = "Controller")
	void SetMyController(APlayerController_Base* SetController);

	UFUNCTION(BlueprintCallable, Category = "Score")
	void SetPlayerScore(float SetAmount);

	UFUNCTION(BlueprintPure, Category = "Score")
	float GetPlayerScore();

	UFUNCTION(BlueprintCallable, Category = "Currency")
	void SetPlayerCurrency(float SetAmount);

	UFUNCTION(BlueprintPure, Category = "Currency")
	float GetPlayerCurrency();
protected:
	UPROPERTY(ReplicatedUsing = OnRep_PlayerScore)
	float PlayerScore;

	UPROPERTY(ReplicatedUsing = OnRep_PlayerCurrency)
	float PlayerCurrency;

	/** Set the mesh colors based on the current teamnum variable */
	void UpdateTeamColors();

	/** team number */
	UPROPERTY(Transient, ReplicatedUsing = OnRep_TeamColor)
	uint8 TeamNumber;

	/** number of kills */
	UPROPERTY(Transient, Replicated)
	int32 NumKills;

	/** number of deaths */
	UPROPERTY(Transient, Replicated)
	int32 NumDeaths;

	/** number of bullets fired this match */
	UPROPERTY()
	int32 NumBulletsFired;

	/** number of rockets fired this match */
	UPROPERTY()
	int32 NumRocketsFired;

	/** whether the user quit the match */
	UPROPERTY()
	uint8 bQuitter : 1;

	/** helper for scoring points */
	void ScorePoints(int32 Points);

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_MyController, Category = "Controller")
	APlayerController_Base* MyController;

	/*Spawn Location*/
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_CharacterSpawnPoint, Category = "Spawn")
	ASpawnPoint_Base* CharacterSpawnPoint;

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_PlayerStartLocation, Category = "Spawn")
	APlayerStart* PlayerStartLocation;

	UFUNCTION()
	void OnRep_PlayerStartLocation();

	UFUNCTION()
	void OnRep_CharacterSpawnPoint();

	UFUNCTION()
	void OnRep_MyController();

	UFUNCTION()
	void OnRep_PlayerScore();

	UFUNCTION()
	void OnRep_PlayerCurrency();
};
