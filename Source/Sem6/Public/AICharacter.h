// YangIsAwesome

#pragma once

#include "CoreMinimal.h"
#include "Character_Base.h"
#include "AICharacter.generated.h"

/**
 * 
 */
UCLASS()
class SEM6_API AAICharacter : public ACharacter_Base
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree* BotBehavior;

	virtual void FaceRotation(FRotator NewRotation, float DeltaTime = 0.f) override;

	virtual bool IsEnemyFor(AController* TestPC) const override;

};
