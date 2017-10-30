// YangIsAwesome

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyType.h"
#include "Shop_Base.generated.h"

UCLASS()
class SEM6_API AShop_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShop_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite, Category = "ShopInventory")
	FItemsToSell ItemsToSell;

public:	

	
};
