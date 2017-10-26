// YangIsAwesome

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyType.h"
#include "GameplayInterface.h"
#include "HighlightInterface.h"
#include "MyBox.generated.h"

UCLASS()
class SEM6_API AMyBox : public AActor,
	public IGameplayInterface,
	public IHighlightInterface
{
	GENERATED_UCLASS_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual ELootAbleType GetLootableType_Implementation() override;

	virtual EWeaponType GetWeaponType_Implementation() override;

	virtual void HighLightActor_Implementation() override;
	void TurnOffCustomDepth();
	FTimerHandle TurnOffRenderCustomDepthHandle;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* MyBoxMesh;

	ELootAbleType LootableType = ELootAbleType::LAT_Box;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Phsyics")
	bool bSetSimulatePhysic(bool bShouldSimulate);

	UStaticMeshComponent* GetStaticMesh();
};
