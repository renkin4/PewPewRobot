// YangIsAwesome

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyType.h"
#include "Interface/GameplayInterface.h"
#include "HighlightInterface.h"
#include "Weapon_Base.generated.h"

class AProjectile_Base;

UCLASS()
class SEM6_API AWeapon_Base : public AActor,
	public IGameplayInterface,
	public IHighlightInterface
{
	GENERATED_UCLASS_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	virtual void HighLightActor_Implementation() override;
	void TurnOffCustomDepth();
	FTimerHandle TurnOffRenderCustomDepthHandle;

	AController* PawnOwner;

	TArray<UStaticMeshComponent*> StaticMeshComp;

	void InstantHitFire();

	void SpawnProjectile(FVector SpawnLoc, FRotator SpawnRot);

	void GetSpawnRotation();
	void GetSpawnLocation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats ")
	FWeaponStats MyStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<AProjectile_Base> ProjectileToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	FVector SocketLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	FRotator SocketRotation;
	//TODO set at Blueprint 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponType")
	EWeaponFireType WeaponFireType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponType")
	EWeaponType WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootableType")
	ELootAbleType LootableType = ELootAbleType::LAT_Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	bool ShowFireLine;

	UPROPERTY(EditAnywhere, Category = "DamageType")
	TSubclassOf<UDamageType> InstantShotDamageType;

	UPROPERTY(EditAnywhere, Category = "DamageType")
	TSubclassOf<UDamageType> ProjectileDamage;

	bool bCanFire;

	FTimerHandle SpawnFireCoolDown;

	void ResetCanFire();
	/*Trajectory*/
	/*Iteration Control*/
	float ElapsedTime = 0.0f;
	float RealDesiredFPS;

	/**FrameRate Persec**/
	UPROPERTY(EditDefaultsOnly, Category = "Trajectory")
	float DesiredFrameRatePS = 15.0f;

	UPROPERTY(EditAnywhere, Category = "Trajectory")
	bool bShowTrajectory;
	UPROPERTY(EditAnywhere, Category = "Trajectory")
	bool bUseShape= false;

	UPROPERTY(EditDefaultsOnly, Category = "Trajectory")
	UParticleSystem* TrajectoryParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Trajectory")
	UParticleSystem* TrajectoryShapeParticle;

	UPROPERTY(EditAnywhere, Category = "Trajectory")
	float TrajectoryMaxDrawDuration = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Trajectory")
	float TrajectoryDrawFrequency = 4.0f;

	void DrawPredictTrajectory();
	/*----------------------*/
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
	FItemToSellInfo WeaponInfomation;

	virtual ELootAbleType GetLootableType_Implementation() override;

	virtual EWeaponType GetWeaponType_Implementation() override;

	UFUNCTION()
	void FireWeapon();

	void SetPawnOwner(AController* Controller);

	UFUNCTION(BlueprintPure, Category = "Weapon Stats")
	float GetWeaponDelay() { return MyStats.ShotsBetweenInterval; }

	UFUNCTION(BlueprintPure, Category = "Weapon State")
	bool CanFire() { return bCanFire; }

	UFUNCTION(BlueprintPure, Category = "Weapon State")
	float GetStaminaCost(){ return MyStats.StaminaCost; }
private:
	FVector2D GetScreenLocation();

	void FilterFireType();

	void DebugLine(FVector Start, FVector End, FColor Color);

};
