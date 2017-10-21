// YangIsAwesome

#include "ProcessDamageInterface.h"

UProcessDamageInterface::UProcessDamageInterface(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

float IProcessDamageInterface::ProcessDamageTypeDamage_Implementation(float Damage, AActor* ActorToIgnore)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CRITICAL ERROR: No ProcessDamageInterface found on ProcessDamageTypeDamage"));
	return 0.0f;
}
