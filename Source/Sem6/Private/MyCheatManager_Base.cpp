// YangIsAwesome

#include "MyCheatManager_Base.h"
#include "PlayerController_Base.h"
#include "Character_Base.h"
#include "PlayerState_Base.h"

UMyCheatManager_Base::UMyCheatManager_Base(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UMyCheatManager_Base::MaxStamina()
{
	ACharacter_Base* MyChar;
	APlayerController* MyPC = Cast<APlayerController>(GetOuter());
	if (MyPC) 
	{
		MyChar = Cast<ACharacter_Base>(MyPC->GetPawn());
		if (MyChar) 
		{
			MyChar->SetStaminaCheatEnabled(!MyChar->GetStaminaCheatEnabled());
		}
	}
}

void UMyCheatManager_Base::SetMyCurrency(float Amount)
{
	APlayerController* MyPC = Cast<APlayerController>(GetOuter());
	if (MyPC)
	{
		APlayerState_Base* PState = Cast<APlayerState_Base>(MyPC->PlayerState);
		if (PState) 
		{
			PState->SetPlayerCurrency(Amount);
		}
	}
}

void UMyCheatManager_Base::God()
{
	MaxStamina();
	Super::God();
}
