// YangIsAwesome

#include "AICharacter.h"
#include "MyAIController.h"
#include "PlayerController_Base.h"

AAICharacter::AAICharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AIControllerClass = AMyAIController::StaticClass();

	bUseControllerRotationYaw = true;
}

void AAICharacter::FaceRotation(FRotator NewRotation, float DeltaTime)
{
	FRotator CurrentRotation = FMath::RInterpTo(GetActorRotation(), NewRotation, DeltaTime, 8.0f);

	Super::FaceRotation(CurrentRotation, DeltaTime);
}

bool AAICharacter::IsEnemyFor(AController * TestPC) const
{
	if (TestPC == Controller || TestPC == NULL)
	{
		return false;
	}

	bool bIsEnemy = false;

	if (TestPC->IsA(APlayerController_Base::StaticClass()))
	{
		bIsEnemy = true;
	}

	return bIsEnemy;
}



