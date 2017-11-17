// YangIsAwesome

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile_Base.generated.h"

UCLASS()
class SEM6_API AProjectile_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float InitialProjectileSpeed = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float ProjectilGravity = 0.1f;

public:	
	UFUNCTION(BlueprintPure, Category = "Projectile Stats")
	float GetInitialProjectileSpeed(){ return InitialProjectileSpeed; }

	UFUNCTION(BlueprintPure, Category = "Projectile Stats")
	float GetProjectileGravity() { return ProjectilGravity; }

	UFUNCTION(BlueprintNativeEvent, Category = "Homing Missle")
	void SetHommingMissle(AActor* TargettedActor);
};
