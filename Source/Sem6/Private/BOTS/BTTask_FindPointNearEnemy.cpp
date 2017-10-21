// YangIsAwesome

#include "BTTask_FindPointNearEnemy.h"
#include "Bots/BTTask_FindPointNearEnemy.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavigationSystem.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "MyAIController.h"
#include "Character_Base.h"

UBTTask_FindPointNearEnemy::UBTTask_FindPointNearEnemy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

EBTNodeResult::Type UBTTask_FindPointNearEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMyAIController* MyController = Cast<AMyAIController>(OwnerComp.GetAIOwner());
	if (MyController == NULL)
	{
		return EBTNodeResult::Failed;
	}

	APawn* MyBot = MyController->GetPawn();
	ACharacter_Base* Enemy = MyController->GetEnemy();
	if (Enemy && MyBot)
	{
		const float SearchRadius = 200.0f;
		const FVector SearchOrigin = Enemy->GetActorLocation() + 600.0f * (MyBot->GetActorLocation() - Enemy->GetActorLocation()).GetSafeNormal();
		FVector RandomLocationOut;
		const bool Loc = UNavigationSystem::K2_GetRandomReachablePointInRadius(GetWorld(), SearchOrigin, RandomLocationOut,SearchRadius);
		if (Loc)
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID(), RandomLocationOut);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
