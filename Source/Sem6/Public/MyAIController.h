// YangIsAwesome

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class SEM6_API AMyAIController : public AAIController
{
	GENERATED_UCLASS_BODY()

private:
	UPROPERTY(transient)
	UBlackboardComponent* BlackboardComp;
	/* Cached BT component */
	UPROPERTY(transient)
	UBehaviorTreeComponent* BehaviorComp;
	//UBehaviorTreeComponent* BehaviorComp;

public:
	void SetEnemy(class APawn* InPawn);

	virtual void GameHasEnded(class AActor* EndGameFocus = NULL, bool bIsWinner = false) override;
	virtual void Possess(class APawn* InPawn) override;
	virtual void UnPossess() override;
	virtual void BeginInactiveState() override;

	void Respawn();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Behavior)
	bool FindClosestEnemyWithLOS(ACharacter_Base* ExcludeEnemy);
	
	/* If there is line of sight to current enemy, start firing at them */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Behavior)
	void ShootEnemy();

	/* Finds the closest enemy and sets them as current target */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Behavior)
	void FindClosestEnemy();

	class ACharacter_Base* GetEnemy() const;

	bool HasWeaponLOSToEnemy(AActor* InEnemyActor, const bool bAnyEnemy);

	// Begin AAIController interface
	/** Update direction AI is looking based on FocalPoint */
	virtual void UpdateControlRotation(float DeltaTime, bool bUpdatePawn = true) override;
	// End AAIController interface

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AICondition")
	void SetStunAI(bool bShouldStun, float StunnedDelay);

	UFUNCTION(BlueprintPure, Category = "AICondition")
	bool GetIsAIStunned() const { return bIsStunned; }

	UPROPERTY(EditAnywhere, Category = "LineOfSight")
	float LineOfSightRangeSq = 1000000.0f;

	UPROPERTY(EditAnywhere, Category = "LineOfSight")
	float DotProductRange;

protected:
	int32 EnemyKeyID;
	int32 IsStunnedID;

	/** Handle for efficient management of Respawn timer */
	FTimerHandle TimerHandle_Respawn;

	bool bHasLOS;

	bool bIsStunned;

	/*Temp*/
	UPROPERTY(EditAnywhere, Category = "Damage")
	TSubclassOf<UDamageType> InstantShotDamageType;

public:
	/** Returns BlackboardComp subobject **/
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	/** Returns BehaviorComp subobject **/
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const { return BehaviorComp; }
};
