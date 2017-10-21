// YangIsAwesome

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_HasLoSTo.generated.h"

/**
 * 
 */
UCLASS()
class SEM6_API UBTDecorator_HasLoSTo : public UBTDecorator
{
	GENERATED_UCLASS_BODY()

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:

	UPROPERTY(EditAnywhere, Category = Condition)
	struct FBlackboardKeySelector EnemyKey;

private:
	bool LOSTrace(AActor* InActor, AActor* InEnemyActor, const FVector& EndLocation) const;
};
