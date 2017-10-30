// YangIsAwesome

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Components/ChildActorComponent.h"
#include "MyBox.h"
#include "SpawnPoint_Base.generated.h"

UCLASS()
class SEM6_API ASpawnPoint_Base : public AActor
{
	GENERATED_UCLASS_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPoint_Base();

protected:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Root")
	USceneComponent* MyRootComp;
	UPROPERTY(VisibleDefaultsOnly, Category = "Location")
	USceneComponent* BoxHolderLocation1;
	UPROPERTY(VisibleDefaultsOnly, Category = "Location")
	USceneComponent* BoxHolderLocation2;
	UPROPERTY(VisibleDefaultsOnly, Category = "Location")
	USceneComponent* BoxHolderLocation3;
	UPROPERTY(VisibleDefaultsOnly, Category = "Location")
	USceneComponent* BoxHolderLocation4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	TArray<USceneComponent*> BoxHolderLocation;

	UPROPERTY()
	TArray<AMyBox*> OccupiedBox;

	UPROPERTY(VisibleDefaultsOnly, ReplicatedUsing = OnRep_BoxHolder,Category = "Mesh")
	UStaticMeshComponent* BoxHolder;

	UMaterial* StoredMaterial;

	UFUNCTION()
	void OnCollisionOverlapped(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCollisionEndOverlaped(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleDefaultsOnly, Category = "Collision")
	UBoxComponent* BoxComponent;

	void SnapTargetToBoxHolderLocation(AActor* ItemToSnapTo, USceneComponent* ItemToSnapAt);

	void ResetBoxHolderLocation();
	void ResetOccupiedBox();
	void SetupComponents();

	UPROPERTY(BlueprintReadWrite,  ReplicatedUsing = OnRep_MyOwner,Category = "SpawnLocation")
	AActor* MyOwner;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BeginPlay")
	void BeginPlayNativeEvent();

	UFUNCTION()
	void OnRep_MyOwner();

	UFUNCTION()
	void OnRep_BoxHolder();

	UFUNCTION(Server, Reliable, WithValidation)
	void SERVER_SetMyOwner(AActor* SetOwner);
public:	
	UFUNCTION(BlueprintPure, Category = "Mesh")
	UStaticMeshComponent* GetMainMesh();

	void SnapBoxToTarget(ACharacter* Player, AActor* Box);

	int GetNumOfBox();

	void DestroyBox();

	UFUNCTION(BlueprintCallable, Category = "SpawnLocation")
	void SetMyOwner(AActor* SetOwner);
};
