// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameMode_Base.h"
#include "Engine/World.h"
#include "Weapon_Base.h"
#include "Loot_Base.h"
#include "Engine.h"
#include "PlayerState_Base.h"
#include "SpawnPoint_Base.h"
#include "MyPlayerStart_Base.h"
#include "MyGameState_Base.h"
#include "PlayerController_Base.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "MyBox.h"

AMyGameMode_Base::AMyGameMode_Base(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bDoOnceOnMatchStart = true;
	bShouldStartMatch = false;
	SetTeamID(0);
}

void AMyGameMode_Base::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	TArray<APlayerState*> PState = GetWorld()->GetGameState()->PlayerArray;
	APlayerState_Base* PStateBase;

	if (HasMatchStarted() && bDoOnceOnMatchStart)
	{
		for (int x = 0; x < PState.Num(); x++) 
		{
			PStateBase = Cast<APlayerState_Base>(PState[x]);
			if (PStateBase) 
			{
				RespawnPlayer(PStateBase->GetMyController());
				ChangeSpawnColor(PStateBase);
			}
		}
		bDoOnceOnMatchStart = false;
	}
}

AActor * AMyGameMode_Base::ChoosePlayerStart_Implementation(AController * Player)
{
	//TODO set a widget to choose Team this is Temp
	AMyPlayerStart_Base* BestPlayerStart = NULL;
	APlayerController_Base* PC = Cast<APlayerController_Base>(Player);
	APlayerState_Base* PState = NULL;
	
	if (PC)
	{
		PState = Cast<APlayerState_Base>(PC->GetPlayerState());
		if (PState)
		{
			if (PState->GetPlayerStartLocation()->IsValidLowLevel())
			{
				return PState->GetPlayerStartLocation();
			}

			for (TActorIterator<AMyPlayerStart_Base> It(GetWorld()); It; ++It)
			{
				AMyPlayerStart_Base* TestSpawn = *It;
				if (!(TestSpawn->GetbIsOwned()) && PC)
				{
					TestSpawn->SetbIsOwned(true);
					TestSpawn->SetTeamNum(PState->GetTeamNum());
					TestSpawn->SetPController(PC);
					BestPlayerStart = TestSpawn;
					PState->SetPlayerStartLocation(BestPlayerStart);
					break;
				}
			}
		}
	}

	return BestPlayerStart;
}

void AMyGameMode_Base::PostLogin(APlayerController * NewPlayer)
{
	APlayerController_Base* PC = Cast<APlayerController_Base>(NewPlayer); 
	APlayerState_Base* PState;
	AMyGameState_Base* GS = Cast<AMyGameState_Base>(GetWorld()->GetGameState());
	uint8 TeamNumHolder;
	if (PC) 
	{
		PState = Cast<APlayerState_Base>(PC->GetPlayerState());
		if (PState)
		{
			if (HasMatchStarted()) 
			{
				//TODO On Drop In Player
				ChangeSpawnColor(PState);
			}
			TeamNumHolder = GetTeamID() + 1;
			SetTeamID(TeamNumHolder);
			PState->SetTeamNum(TeamNumHolder);
			PState->SetMyController(PC);
			/*Pass in Information To Update Everyone*/
			PC->UpdateSelectionUI();
		}
	}
	
	Super::PostLogin(NewPlayer);
}

bool AMyGameMode_Base::ShouldSpawnAtStartSpot(AController * Player)
{
	return false;
}

bool AMyGameMode_Base::ReadyToStartMatch_Implementation()
{
	return bShouldStartMatch;
}

void AMyGameMode_Base::ChangeSpawnColor_Implementation(APlayerState_Base* PState, UMaterialInterface * MaterialInterface = NULL)
{
	PState->CLIENT_UpdateColorOfSpawn(PState->GetSpawnLocation()->GetMainMesh(), MaterialInterface);
}

void AMyGameMode_Base::SetShouldStartMatch(bool bSetMatchStart)
{
	bShouldStartMatch = bSetMatchStart;
}

void AMyGameMode_Base::SetTeamID(uint8 SetTeamID)
{
	TeamID = SetTeamID;
}

uint8 AMyGameMode_Base::GetTeamID()
{
	return TeamID;
}

void AMyGameMode_Base::RespawnPlayer(APlayerController * PController)
{
	if (PController->GetPawn()->IsValidLowLevel())
	{
		PController->GetPawn()->Destroy();
	}
	RestartPlayer(PController);
}

AWeapon_Base* AMyGameMode_Base::SpawnWeapon(TSubclassOf<AWeapon_Base> WeaponClass, const FVector Location, const FRotator Rotation)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	return GetWorld()->SpawnActor<AWeapon_Base>(WeaponClass, Location, Rotation, SpawnInfo);
}

ALoot_Base* AMyGameMode_Base::SpawnLoot(TSubclassOf<ALoot_Base> LootClass, const FVector Location, const FRotator Rotation)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	return GetWorld()->SpawnActor<ALoot_Base>(LootClass, Location, Rotation, SpawnInfo);
}

AMyBox* AMyGameMode_Base::SpawnBox(TSubclassOf<AMyBox> BoxClass, const FVector Location, const FRotator Rotation)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	return GetWorld()->SpawnActor<AMyBox>(BoxClass, Location, Rotation, SpawnInfo);
}

ASpawnPoint_Base* AMyGameMode_Base::SpawnBase(TSubclassOf<ASpawnPoint_Base> SpawnPoint_Base_Class, const FVector Location, const FRotator Rotation)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	SpawnInfo.Owner = this;
	SpawnInfo.Instigator = NULL;

	return GetWorld()->SpawnActor<ASpawnPoint_Base>(SpawnPoint_Base_Class, Location, Rotation, SpawnInfo);
}

void AMyGameMode_Base::ChangeSpawnPointColour(APlayerState_Base * PState, UStaticMeshComponent * MeshToChangeColor, UMaterialInterface * MaterialChangeTo)
{
	if (PState) 
	{
		PState->CLIENT_UpdateColorOfSpawn(MeshToChangeColor, MaterialChangeTo);
	}
	return;
}

void AMyGameMode_Base::BeginPlay()
{
	Super::BeginPlay();

}
