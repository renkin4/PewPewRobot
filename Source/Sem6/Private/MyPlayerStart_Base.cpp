// YangIsAwesome

#include "MyPlayerStart_Base.h"
#include "MyGameMode_Base.h"

AMyPlayerStart_Base::AMyPlayerStart_Base(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bIsOwned = false;
}

void AMyPlayerStart_Base::BeginPlay() 
{
	Super::BeginPlay();
}

void AMyPlayerStart_Base::SetSpawnPointBase(ASpawnPoint_Base * SpawnBaseToSet)
{
	SpawnPointBase = SpawnBaseToSet;
}

ASpawnPoint_Base * AMyPlayerStart_Base::GetSpawnPointBase()
{
	return SpawnPointBase;
}

void AMyPlayerStart_Base::SetTeamNum(uint8 SetTeamNum)
{
	TeamNum = SetTeamNum;
}

uint8 AMyPlayerStart_Base::GetTeamNum()
{
	return TeamNum;
}

bool AMyPlayerStart_Base::GetbIsOwned()
{
	return bIsOwned;
}

void AMyPlayerStart_Base::SetbIsOwned(bool bSetIsOwned)
{
	bIsOwned = bSetIsOwned;
}

APlayerController * AMyPlayerStart_Base::GetPController()
{
	return PController;
}

void AMyPlayerStart_Base::SetPController(APlayerController* Controller)
{
	PController = Controller;
}
