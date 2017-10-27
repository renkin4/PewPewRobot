//YangIsAwesome

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyType.h"
#include "Interface/GameplayInterface.h"
#include "Interface/ProcessDamageInterface.h"
#include "Character_Base.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCollectDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUseLootableDelegate);

class APlayerState_Base;

UCLASS()
class SEM6_API ACharacter_Base : public ACharacter,
	public IGameplayInterface,
	public IProcessDamageInterface
{
	GENERATED_BODY()
	friend class UMyCharacterMovementComponent;

public:
	// Sets default values for this character's properties
	ACharacter_Base(const class FObjectInitializer& ObjectInitializer);

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController * NewController) override;

	/*Replication Override*/
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	virtual ELootAbleType GetLootableType_Implementation() override;

	virtual EWeaponType GetWeaponType_Implementation() override;

	virtual float ProcessDamageTypeDamage_Implementation(float Damage, AActor* ActorToIgnore) override;

	/*Internal Movement*/
	void MoveForward(float axis);
	void MoveRight(float axis);
	void PitchLookUp(float axis);
	void YawTurn(float axis);
	/*----------------------------------------------------*/

	/*Internal Actions*/
	void OnJump();
	void OnAim();
	void OnCollect();
	void OnCollectRelease();
	void OnScore();
	void OnFire();
	void OnReleaseFire();
	void OnRun();
	void OnWalk();
	void OnReleasedAim();
	void OnUseLootable();
	void OnSwitchSelection();

	UPROPERTY(BlueprintAssignable)
	FOnCollectDelegate OnCollectDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnUseLootableDelegate OnUseLootableDelegate;

	UFUNCTION()
	void CollectItem();

	bool bOnCollectDoOnce;
	bool bBindDynamicDoOnce;
	/*----------------------------------------------------*/

	/*Running*/
	/*Replication*/
	UPROPERTY(Transient, Replicated)
	bool bIsRunning;

	UFUNCTION(Server, Reliable, WithValidation)
	void SERVER_SetRunnning(bool bNewIsRunning);

	UFUNCTION(Server, WithValidation, Reliable)
	void SERVER_OnScore();

	void OnKickScoreBox();

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_MyPlayerController, Category = "Controller")
	APlayerController_Base* MyPlayerController = NULL;

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_MyPlayerState, Category = "PlayerState")
	APlayerState_Base* MyPlayerState = NULL;

	UFUNCTION()
	void OnRep_MyPlayerController();
	/*Stamina // Mana*/
	UPROPERTY(ReplicatedUsing = OnRep_Stamina)
	float Stamina;
	float MaxStamina;

	UFUNCTION(BlueprintNativeEvent, Category = "Stamina")
	void OnRep_Stamina();

	UPROPERTY(BlueprintReadWrite, Category = "Stamina")
	float AsthethicStaminaVal;

	UPROPERTY(EditAnywhere, Category = "Stamina")
	float DelayBeforeRegenStamina = 2.0f;
	UPROPERTY(EditAnywhere, Category = "Stamina")
	float RegenRate = 100.0f;

	bool bShouldRegenStamina;

	void RegenStamina();
	void TriggerRegenStamina();
	FTimerHandle DelayStaminaRegenHandle;

	UFUNCTION(Server, WithValidation, Reliable)
	void SERVER_SetStaminaVal(float NewVal);
	/*----------------------------------------------------*/
	/*Health*/
	bool bDie;
	bool bIsDying;

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_Health, Category = "Health")
	float Health;

	UPROPERTY(BlueprintReadWrite, Category = "Health")
	float LocalHealth;

	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Health")
	float MaxHealth;

	float ActualDamage;

	UFUNCTION(BlueprintNativeEvent, Category = "Health")
	void OnRep_Health();

	UFUNCTION(BlueprintNativeEvent, Category = "Death")
	void OnDeathNotify();
	/*----------------------------------------------------*/

	UPROPERTY(EditAnywhere, Category = "WalkMovement")
	float RunningSpeedModifier;
	float WalkSpeedModifier;
	UFUNCTION(BlueprintPure, Category = "WalkMovement")
	bool CanRun();

	AMyBox* MyHoldingBox;
	
	UPROPERTY(BlueprintReadWrite, Category = "State")
	bool bIsHoldingBox;
	bool bIsTargeting;
	bool bIsCarrying;
	bool bIsGettingShot;
	UPROPERTY(BlueprintReadWrite, Replicated,Category = "SpawnLocation")
	bool bIsAtBoxHolderLocation;

	UFUNCTION(Server, Reliable, WithValidation)
	void SERVER_SetOnSimulatePhysic( AActor* ActorToSimulate, bool bShouldSimulate);

	bool bSetOnSimulatePhysic( AActor* ActorToSimulate, bool bShouldSimulate);

	/*----------------------------------------------------*/

	/*Animation*/
	UPROPERTY(EditAnywhere, Category = "Animation")
	class UAnimMontage* PunchingMontage;

	UPROPERTY(EditAnywhere, Category = "Animation")
	class UAnimMontage* ShootingMontage;

	UPROPERTY(EditAnywhere, Category = "Animation")
	class UAnimMontage* CarryingBoxMontage;

	UPROPERTY(EditAnywhere, Category = "Animation")
	class UAnimMontage* RocketLauncherMontage;

	UPROPERTY(EditAnywhere, Category = "Animation")
	class UAnimMontage* DeathMontage;

	UFUNCTION(NetMultiCast, Reliable)
	void MULTICAST_PlayAnimMontage(UAnimMontage * Montage, float InPlayRate, FName StartSectionName);

	UFUNCTION(Server, Reliable, WithValidation)
	void SERVER_PlayAnimMontage(UAnimMontage * Montage, float InPlayRate, FName StartSectionName);

	UFUNCTION(NetMultiCast, Reliable)
	void MULTICAST_StopAnimMontage(UAnimMontage * Montage);

	UFUNCTION(Server, Reliable, WithValidation)
	void SERVER_StopAnimMontage(UAnimMontage * Montage);

	UFUNCTION(NetMultiCast, Reliable)
	void MULTICAST_SwitchAnimMontage(FName CurrentSection, FName NextSection, UAnimMontage * Montage);

	UFUNCTION(Server, Reliable, WithValidation)
	void SERVER_SwitchAnimMontage(FName CurrentSection, FName NextSection, UAnimMontage * Montage);

	void PlayAnimationState();
	void PlayTypeOfWeaponAnimation(EWeaponType WeaponType);

	void OnHoldBox();
	void OnDropBox();
	UFUNCTION(BlueprintPure, Category = "Lootable")
	bool CanLoot();

	UFUNCTION(Server, WithValidation, Reliable)
	void SERVER_OnSnapBoxToLocation(AMyBox* BoxToSnapTo);

	void OnSnapBoxToLocation(AMyBox* BoxToSnapTo);
	/*----------------------------------------------------*/

	/*Enums and Struct*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enum")
	ECharacterState CharacterState;
	UPROPERTY(BlueprintReadWrite, Replicated,Category = "Inventory")
	FCharacterInvetory Inventory;

	void LootableFilter();

	/*Weapon*/
	UFUNCTION(BlueprintPure, Category = "Weapon")
	bool CanFire();
	void SetWeaponVisible(AWeapon_Base* WeaponToHide, bool bShouldHide);
	void OnLootWeapon();
	void OnPunch();
	void OnPunchNotify();
	
	UPROPERTY(EditAnywhere, Category = "Damage")
	TSubclassOf<UDamageType> OnePunchDamageClass;

	UFUNCTION(Server, WithValidation, Reliable)
	void SERVER_SetWeaponVisible(AWeapon_Base* WeaponToHide, bool bShouldHide);

	UFUNCTION(BlueprintCallable, Category = "Mesh")
	void AttachActorToMesh(AActor* WeaponToAttach);

	UFUNCTION(BlueprintCallable, Category = "Mesh")
	void DetachActorFromMesh(AActor* ActorToDettach);

	UFUNCTION(BlueprintCallable, Category = "Mesh")
	void SetLootableCollision(UStaticMeshComponent* ActorComponentToSet, ECollisionChannel SetChannel, ECollisionResponse ChannelResponse);

	void SetOnHoldAndDropCollision(UStaticMeshComponent* StaticMeshComponent,ECollisionResponse ChannelResponse);

	UFUNCTION(Server, WithValidation, Reliable)
	void SERVER_OnPunch();

	//TODO set Current Weapon on Rep Notify
	AWeapon_Base* CurrentWeapon;
	AWeapon_Base* PreviousWeapon;

	FTimerHandle ShootingHandler;
	FTimerHandle PunchingHandler;
	FTimerHandle HoldingBoxHandler;
	FTimerHandle DeathTimeHandler;

	void OnDeathNotifyTimerRespawn();

	UFUNCTION(NetMultiCast, Reliable)
	void MULTICAST_AttachEquip(AActor* ActorToAttach, const FName SocketName);

	UFUNCTION(Server, Reliable, WithValidation)
	void SERVER_AttachEquip(AActor* ActorToAttach);

	UFUNCTION(NetMultiCast, Reliable)
	void MULTICAST_DettachEquip(AActor* ActorToDettach);

	UFUNCTION(Server, Reliable, WithValidation)
	void SERVER_DettachEquip(AActor* ActorToDettach);

	UFUNCTION(NetMultiCast, Reliable)
	void MULTICAST_SetCollision(UStaticMeshComponent* ActorComponentToSet, ECollisionChannel SetChannel, ECollisionResponse ChannelResponse);

	UFUNCTION(Server, Reliable, WithValidation)
	void SERVER_SetCollision(UStaticMeshComponent* ActorComponentToSet, ECollisionChannel SetChannel, ECollisionResponse ChannelResponse);

	void FireWeapon();
	void SetCurrentWeapon(AWeapon_Base* Weapon);
	/*----------------------------------------------------*/
	/*Items*/
	void OnLootLootable(ALoot_Base* MyCharacter);

	UFUNCTION(Server, Reliable, WithValidation)
	void SERVER_OnLootLootable(ALoot_Base* MyCharacter);

	UFUNCTION(NetMultiCast, Reliable)
	void MULTICAST_OnLootLootable(ALoot_Base* MyCharacter);

	UFUNCTION(Server, Reliable, WithValidation)
	void SERVER_UseLootable();

	UFUNCTION(BlueprintNativeEvent, Category = "Lootable")
	void UseLootable();
	/*----------------------------------------------------*/
	/*Trace*/
	TArray<FHitResult> LootableOutHit;
	bool SphereTraceLootable();
	
	void DrawSphereDebugLine(float Radius, FVector CenterLocation, FColor Color);

	int32 SelectedItemIndex;

	/*----------------------------------------------------*/
	/*Team Color*/
	UPROPERTY(EditAnywhere, Category = "Team Color")
	TArray<UMaterialInstance*> TeamColorMat;

	void UpdateColor(APlayerState_Base* PState, USkeletalMeshComponent* SMesh);

	UFUNCTION(Server,Reliable,WithValidation)
	void SERVER_UpdateColor(APlayerState_Base* PState, USkeletalMeshComponent* SMesh);

	UFUNCTION(NetMulticast, Reliable)
	void MULTICAST_UpdateColor(APlayerState_Base* PState, USkeletalMeshComponent* SMesh);

	FTimerHandle UpdateColorTimeHandler;
	/*----------------------------------------------------*/
	/*Debug*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	bool bEnableLootableSphere;

public:
	void SetMyPlayerController(APlayerController_Base* MyPlayerControllerRef);

	UFUNCTION(BlueprintPure, Category = "PlayerController")
	APlayerController_Base* GetMyPlayerController();

	void SetMyPlayerState(APlayerState_Base* MyPlayerStateRef);

	void SetRunnning(bool bNewIsRunning);

	UFUNCTION(BlueprintCallable, Category = Pawn)
	bool IsRunning() const;

	UFUNCTION(BlueprintPure, Category = Pawn)
	bool IsAlive();

	virtual bool IsEnemyFor(AController* TestPC) const;

	bool SetIsAtBoxLocation(bool bIsNearLocation);

	UFUNCTION(BlueprintPure, Category = "CharacterState")
	bool GetIsTargetting() { return bIsTargeting; }

	UFUNCTION(BlueprintPure, Category = "Loot")
	FHitResult GetCurrentSelectedItem();

	UFUNCTION()
	void OnRep_MyPlayerState();

	UFUNCTION(BlueprintPure, Category = "Stamina")
	float GetStaminaVal() {return Stamina;}

	UFUNCTION(BlueprintPure, Category = "Stamina")
	float GetMaxStaminaVal() { return MaxStamina; }

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	float SetStamina(float StaminaVal, bool DrainStamina);

};
