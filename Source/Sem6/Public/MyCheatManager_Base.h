// YangIsAwesome

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "MyCheatManager_Base.generated.h"

/**
 * 
 */
UCLASS()
class SEM6_API UMyCheatManager_Base : public UCheatManager
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(Exec, Category = "Console Command")
	void MaxStamina();

	virtual void God() override;
};
