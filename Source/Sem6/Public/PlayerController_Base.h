// YangIsAwesome

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Components/TimelineComponent.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "PlayerController_Base.generated.h"

/**
 * 
 */
UCLASS()
class SEM6_API APlayerController_Base : public APlayerController
{
	GENERATED_BODY()
public:
	APlayerController_Base(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintPure)
	bool GetIsAiming();

	UFUNCTION(BlueprintCallable)
	bool SetIsAiming(bool bShouldAim);

	UFUNCTION(Client, Reliable)
	void CLIENT_PawnChanged();

	UFUNCTION()
	APlayerState* GetPlayerState();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void RespawnPlayer();

	AActor* SpawnProjectile(FVector SpawnLoc, FRotator SpawnRot, TSubclassOf<AActor> ProjectileToSpawn, AActor* ProjOwner);

	/*Lobby*/
	UFUNCTION(BlueprintCallable, Category = "Lobby")
	void UpdateSelectionUI();

	UFUNCTION(BlueprintCallable, Category = "Lobby")
	void UpdateReadyStatus();

	UFUNCTION(BlueprintCallable, Category = "Lobby")
	void OnJoinTeam(uint8 TeamNum);

	UFUNCTION(BlueprintCallable, Category = "Lobby")
	void OnLeaveTeam(uint8 TeamNum);

	UFUNCTION(BlueprintCallable, Category = "Lobby")
	void SetReady(bool bShouldReady);

	/*---------------------------------------------*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void ProcessPlayerInput(const float DeltaTime, const bool bGamePaused) override;

	virtual void Possess(APawn * InPawn) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Pawn")
	void OnPossessEvent(APawn * InPawn);

	void InitializeVarOnPossessed(ACharacter* MyChar ,APlayerController_Base* SelfPController, APlayerState_Base* SelfPlayerState);

	UFUNCTION(Server, WithValidation, Reliable)
	void SERVER_InitializeVarOnPossessed(ACharacter* MyChar,APlayerController_Base* SelfPController, APlayerState_Base* SelfPlayerState);

	void OnAim();
	void OnReleasedAim();

	bool bIsAiming;

	UPROPERTY()
	UTimelineComponent* AimTimeline;

	UPROPERTY(EditAnywhere, Category = "Aiming")
	UCurveFloat* AimingFloatCurve;
	FOnTimelineFloat InterpFunction{};
	FOnTimelineEvent OnAimTimelineFinishEvent{};

	UFUNCTION()
	void AimTimelineFloatReturn(float val);

	UFUNCTION()
	void AimOnTimelineFinish();

	UPROPERTY(EditAnywhere, Category = "Aiming")
	float SpringAimLengthModifier;
	
	FVector SpringArmDefaultRelativeLocation;
	float SpringArmDefaultRelativeArmLength;
	void SetCharacterControlledYaw(bool bIsFollow);
	
	UFUNCTION(Server, WithValidation, Reliable)
	void SERVER_SetCharacterControlledYaw(bool bIsFollow, ACharacter* CharacterOwner);

	UFUNCTION(Client, Reliable)
	void CLIENT_SetCharacterControlledYaw(bool bIsFollow);
	/*---------------------------------------------*/
	/** Holding the current Character for the controller */
	ACharacter* MyCharacter;
	/*---------------------------------------------*/
	TArray<USpringArmComponent*> SpringArmComp;
	TArray<UChildActorComponent*> ZoomLocation;
	/*---------------------------------------------*/
	UFUNCTION(Server, WithValidation, Reliable)
	void SERVER_RespawnPlayer();
	/*---------------------------------------------*/
	UFUNCTION(Server, WithValidation, Reliable)
	void SERVER_SpawnProjectile(FVector SpawnLoc, FRotator SpawnRot, TSubclassOf<AActor> ProjectileToSpawn, AActor* ProjOwner);
	/*---------------------------------------------*/
	/*Lobby*/
	UFUNCTION(Server, WithValidation, Reliable)
	void SERVER_UpdateSelectionUI();

	UFUNCTION(Server, WithValidation, Reliable)
	void SERVER_UpdateReadyStatus();

	UFUNCTION(Server, WithValidation, Reliable)
	void SERVER_OnJoinTeam(uint8 TeamNum);

	UFUNCTION(Server, WithValidation, Reliable)
	void SERVER_OnLeaveTeam(uint8 TeamNum);

	UFUNCTION(Server, WithValidation, Reliable)
	void SERVER_SetReady(bool bShouldReady);

	void DelayOnUpdateSelectionUI();

	FTimerHandle DelayOnUpdateSelectionUIHandle;
	/*---------------------------------------------*/
private:
	/*Cheats*/
	UFUNCTION(Exec, Category = "Console Command")
	void MaxStamina();
	UFUNCTION(Exec, Category = "Console Command")
	void SetMyCurrency(float Amount);
	UFUNCTION(Exec, Category = "Console Command")
	void YangIsAwesome();

	UFUNCTION(Server,WithValidation,Reliable)
	void SERVER_MaxStamina();
	UFUNCTION(Server, WithValidation, Reliable)
	void SERVER_SetMyCurrency(float Amount);
	UFUNCTION(Server, WithValidation, Reliable)
	void SERVER_YangIsAwesome();
	/*---------------------------------------------*/
};
