// YangIsAwesome

#pragma once

#include "CoreMinimal.h"
#include "HighlightInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class UHighlightInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IHighlightInterface
{
	GENERATED_IINTERFACE_BODY()

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HighlightInterface", meta = (DisplayName = "High Light Actor"))
	void HighLightActor();

};
