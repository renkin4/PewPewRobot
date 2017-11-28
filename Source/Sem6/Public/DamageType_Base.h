// YangIsAwesome

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "Interface/ProcessDamageInterface.h"
#include "DamageType_Base.generated.h"

/**
 * 
 */
UCLASS()
class SEM6_API UDamageType_Base : public UDamageType,
	public IProcessDamageInterface
{
	GENERATED_UCLASS_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Damage")
	float StunDuration;

protected:
	virtual float ProcessDamageTypeDamage_Implementation(float Damage, AActor* ActorToIgnore) override;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float Multiplier;

	UPROPERTY(EditAnywhere, Category = "Damage")
	TSubclassOf<AActor> M_ActorToIgnore;
	
	
};
