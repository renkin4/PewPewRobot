// YangIsAwesome

#pragma once

#include "CoreMinimal.h"
#include "MyType.h"
#include "ProcessDamageInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class UProcessDamageInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IProcessDamageInterface
{
	GENERATED_IINTERFACE_BODY()

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ProcessDamageInterface", meta = (DisplayName = "ProcessDamageTypeDamage"))
	float ProcessDamageTypeDamage(float Damage);
};
