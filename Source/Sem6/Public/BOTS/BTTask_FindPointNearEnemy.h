// YangIsAwesome

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindPointNearEnemy.generated.h"

/**
 * 
 */
UCLASS()
class SEM6_API UBTTask_FindPointNearEnemy : public UBTTask_BlackboardBase
{
	GENERATED_UCLASS_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	
	
};
