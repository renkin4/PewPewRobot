// YangIsAwesome

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/GameplayInterface.h"
#include "MyType.h"
#include "PlayerController_Base.h"
#include "Weapon_Base.generated.h"

UCLASS()
class SEM6_API AWeapon_Base : public AActor,
	public IGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AController* PawnOwner;

	TArray<UStaticMeshComponent*> StaticMeshComp;

	void InstantHitFire();

	//TODO set at Blueprint 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponType")
	EWeaponFireType WeaponFireType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponType")
	EWeaponType WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootableType")
	ELootAbleType LootableType = ELootAbleType::LAT_Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	bool ShowFireLine;

public:	

	virtual ELootAbleType GetLootableType_Implementation() override;

	virtual EWeaponType GetWeaponType_Implementation() override;

	UFUNCTION()
	void FireWeapon();

	void SetPawnOwner(AController* Controller);

private:
	FVector2D GetScreenLocation();

	void RayCastFromMiddle();

	void DebugLine(FVector Start, FVector End, FColor Color);

};
