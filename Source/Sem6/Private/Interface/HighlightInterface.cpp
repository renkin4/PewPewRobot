// YangIsAwesome

#include "HighlightInterface.h"

UHighlightInterface::UHighlightInterface(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void IHighlightInterface::HighLightActor_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CRITICAL ERROR: No HighlightInterface found on HighLightActor"));
	return;
}
