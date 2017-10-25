// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterMovementComponent.h"
#include "Character_Base.h"

float UMyCharacterMovementComponent::GetMaxSpeed() const
{
	float SpeedMod = Super::GetMaxSpeed();;
	ACharacter_Base* MyCharacter = Cast<ACharacter_Base>(PawnOwner);

	if (MyCharacter)
	{

		if (MyCharacter->IsRunning() && MyCharacter->CanRun())
		{
			SpeedMod *= MyCharacter->RunningSpeedModifier;
			MyCharacter->SetStamina(MyCharacter->GetStaminaVal() - StaminaConsumption);
		}
		//TODO check for !targetting and !Carrying
		else
		{
			SpeedMod *= MyCharacter->WalkSpeedModifier;
		}
	
	}

	return SpeedMod;
}
