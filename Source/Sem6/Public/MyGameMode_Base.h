// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerStart.h"
#include "MyGameMode_Base.generated.h"

class AMyPlayerStart_Base;
class PlayerState_Base;

/**
 * 
 */
UCLASS()
class SEM6_API AMyGameMode_Base : public AGameMode
{
	GENERATED_UCLASS_BODY()
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadWrite, Category = "Team")
	uint8 TeamID;

	/*Select Pawn Base or place to spawn*/
	virtual AActor* ChoosePlayerStart_Implementation(AController * Player) override;

	/*On Player login to Session*/
	virtual void PostLogin(APlayerController * NewPlayer) override;

	virtual bool ShouldSpawnAtStartSpot(AController * Player) override;

	virtual bool ReadyToStartMatch_Implementation() override;

	/** The bot pawn class */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameMode)
	TSubclassOf<APawn> BotPawnClass;

	bool bShouldStartMatch;
	
	bool bDoOnceOnMatchStart;

	UPROPERTY(BlueprintReadWrite, Category = "Gameplay")
	TArray<AActor*> Crates;

public:
	UFUNCTION(BlueprintCallable, Category = "MatchStart")
	void SetShouldStartMatch(bool bSetMatchStart);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpawnLocation")
	void ChangeSpawnColor(APlayerState_Base* PState, UMaterialInterface* MaterialInterface = NULL);

	UFUNCTION(BlueprintCallable, Category = "Team")
	void SetTeamID(uint8 SetTeamID);

	UFUNCTION(BlueprintPure, Category = "Team")
	uint8 GetTeamID();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void RespawnPlayer(APlayerController* PController);

	/*Spawn Actors*/
	UFUNCTION(BlueprintCallable, Category = "SpawnActor")
	AWeapon_Base* SpawnWeapon(TSubclassOf<AWeapon_Base> WeaponClass, const FVector Location, const FRotator Rotation);

	UFUNCTION(BlueprintCallable, Category = "SpawnActor")
	ALoot_Base* SpawnLoot(TSubclassOf<ALoot_Base> LootClass, const FVector Location, const FRotator Rotation);

	UFUNCTION(BlueprintCallable, Category = "SpawnActor")
	AMyBox* SpawnBox(TSubclassOf<AMyBox> BoxClass, const FVector Location, const FRotator Rotation);

	UFUNCTION(BlueprintCallable, Category = "SpawnActor")
	ASpawnPoint_Base* SpawnBase(TSubclassOf<ASpawnPoint_Base> SpawnPoint_Base_Class, const FVector Location, const FRotator Rotation);

	/*----------------------------*/
	UFUNCTION(BlueprintCallable, Category = "MeshColor")
	void ChangeSpawnPointColour(APlayerState_Base* PState, UStaticMeshComponent* MeshToChangeColor, UMaterialInterface* MaterialChangeTo);
};
