// YangIsAwesome

#include "DamageType_Base.h"

UDamageType_Base::UDamageType_Base(const class FObjectInitializer& ObjectInitializer)
:Super(ObjectInitializer)
{

}

float UDamageType_Base::ProcessDamageTypeDamage_Implementation(float Damage, AActor* ActorToIgnore)
{
	if (M_ActorToIgnore == ActorToIgnore->GetClass())
		return 0.0f;

	float ActualDamage = Damage * Multiplier;
	return ActualDamage;
}
