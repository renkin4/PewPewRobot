// YangIsAwesome

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyType.h"
#include "Interface/GameplayInterface.h"
#include "HighlightInterface.h"
#include "Weapon_Base.generated.h"

class AProjectile_Base;
class UBoxComponent;

USTRUCT()

struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	/** inifite ammo for reloads */
	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	bool bInfiniteAmmo;

	/** infinite ammo in clip, no reload required */
	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	bool bInfiniteClip;

	/** max ammo */
	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	int32 MaxAmmo;

	/** clip size */
	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	int32 AmmoPerClip;

	/** initial clips */
	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	int32 InitialClips;

	/** failsafe reload duration if weapon doesn't have any animation for it */
	UPROPERTY(EditDefaultsOnly, Category = WeaponStat)
	float NoAnimReloadDuration;

	/** defaults */
	FWeaponData()
	{
		bInfiniteAmmo = false;
		bInfiniteClip = false;
		MaxAmmo = 100;
		AmmoPerClip = 20;
		InitialClips = 4;
		NoAnimReloadDuration = 1.0f;
	}
};
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Stats ")
	FWeaponData WeaponData;

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

	UFUNCTION(BlueprintCallable, Category = "Trajectory")
	void DrawPredictTrajectory();

	UFUNCTION(BlueprintCallable, Category = "Trajectory")
	void FlushTrajectoryProjectile();

	UPROPERTY(BlueprintReadOnly, Category = "Trajectory")
	TArray<UParticleSystemComponent*> TrajectoryPathSegPSArray;

	FTimerHandle ResetTrajectory;
	/*----------------------*/

public:	
	UFUNCTION(BlueprintNativeEvent, Category = "Missile")
	void HommingMissleTargetTrace();

	UPROPERTY(EditDefaultsOnly, Category = "Missile")
	bool bIsHomming;

	FTimerHandle ResetHomingLauncherHandle;

	void ResetHomingLauncher();

	AActor* HommingTarget;

	void OnBeginOverlapComponentForLockOn(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
	FItemToSellInfo WeaponInfomation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Icon")
	UTexture2D* MyIcon;

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

	UFUNCTION(BlueprintPure, Category = "Controller")
	AController* GetPawnOwner() { return PawnOwner; }

	UFUNCTION(BlueprintPure, Category = "Weapon State")
	EWeaponFireType GetWeaponFireType() { return WeaponFireType; }

	UFUNCTION(BlueprintCallable, Category = "Trajectory")
	void DrawTrajectory();

private:
	FVector2D GetScreenLocation();

	void FilterFireType();

	void DebugLine(FVector Start, FVector End, FColor Color);

};
