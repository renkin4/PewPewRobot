// YangIsAwesome

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SEM6_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	bool IsAlive;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	bool IsRunning;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	bool IsMoving;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	bool IsFalling;

};
