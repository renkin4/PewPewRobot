#include "CoreMinimal.h"
#include "MyType.generated.h"
#pragma once

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	CS_Walk 			UMETA(DisplayName = "Walk"),
	CS_Run 				UMETA(DisplayName = "Run"),
	CS_Carry			UMETA(DisplayName = "Carry"),
	CS_Targetting		UMETA(DisplayName = "Targetting"),
	CS_HoldingGun		UMETA(DisplayName = "HoldingGun"),
	CS_Firing			UMETA(DisplayName = "Firing"),
	CS_HoldingRocket	UMETA(DisplayName = "HoldingRocket"),
	CS_FiringRocket		UMETA(DisplayName = "FiringRocket"),
	CS_Punching			UMETA(DisplayName = "Punching")
};

UENUM(BlueprintType)
enum class EWeaponFireType : uint8
{
	WT_None				UMETA(DisplayName = "None"),
	WT_InstantHit		UMETA(DisplayName = "InstantHit"),
	WT_ProjecTile		UMETA(DisplayName = "Projectile")
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	WT_None				UMETA(DisplayName = "None"),
	WT_MachineGun		UMETA(DisplayName = "MachineGun"),
	WT_RocketLauncher	UMETA(DisplayName = "RocketLauncher")
};

UENUM(BlueprintType)
enum class ECharacterPowerUp : uint8
{
	CPU_Shield,
	CPU_TargetPlayer
};

UENUM(BlueprintType)
enum class ELootAbleType : uint8
{
	LAT_None,
	LAT_Box,
	LAT_Weapon,
	LAT_PowerUp
};

USTRUCT(BlueprintType) 
struct FCharacterInvetory
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	bool bIsWeaponExist;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<AActor*> Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<TSubclassOf<AActor>> PowerUp;

};


USTRUCT(BlueprintType)
struct FLootableStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootableStruct")
	float Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootableStruct")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootableStruct")
	TSubclassOf<AActor> ActorClass;
};

USTRUCT(BlueprintType)
struct FItemsToSell
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
	TArray<TSubclassOf<AActor>> ActorClass;

};

USTRUCT(BlueprintType)
struct FWeaponStats 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats ")
	float ShotsBetweenInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats ")
	float RadialRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats ")
	float StunDelayDuration;
};