// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerState_Base.h"
#include "Character_Base.h"
#include "Runtime/Engine/Classes/Engine/StaticMesh.h"
#include "MyGameState_Base.h"
#include "PlayerController_Base.h"
#include "MyPlayerStart_Base.h"
#include "SpawnPoint_Base.h"
#include "Net/UnrealNetwork.h"


#define MAX_PLAYER_NAME_LENGTH 16

APlayerState_Base::APlayerState_Base(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	TeamNumber = 0;
	NumKills = 0;
	PlayerScore = 0.0f;
	PlayerCurrency = 0.0f;
	NumDeaths = 0;
	NumBulletsFired = 0;
	NumRocketsFired = 0;
	bPlayerIsReady = false;
	bQuitter = false;
	PlayerStartLocation = NULL;
}

void APlayerState_Base::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerState_Base::Reset()
{
	Super::Reset();

	//PlayerStates persist across seamless travel.  Keep the same teams as previous match.
	//SetTeamNum(0);
	NumKills = 0;
	NumDeaths = 0;
	NumBulletsFired = 0;
	NumRocketsFired = 0;
	bQuitter = false;
}

void APlayerState_Base::UnregisterPlayerWithSession()
{
	if (!bFromPreviousLevel)
	{
		Super::UnregisterPlayerWithSession();
	}
}

void APlayerState_Base::ClientInitialize(AController* InController)
{
	Super::ClientInitialize(InController);
}

void APlayerState_Base::SetTeamNum(uint8 NewTeamNumber)
{
	TeamNumber = NewTeamNumber;
}

void APlayerState_Base::OnRep_TeamNumber()
{
}

void APlayerState_Base::AddBulletsFired(int32 NumBullets)
{
	NumBulletsFired += NumBullets;
}

void APlayerState_Base::AddRocketsFired(int32 NumRockets)
{
	NumRocketsFired += NumRockets;
}

void APlayerState_Base::SetQuitter(bool bInQuitter)
{
	bQuitter = bInQuitter;
}

void APlayerState_Base::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	APlayerState_Base* ShooterPlayer = Cast<APlayerState_Base>(PlayerState);
	if (ShooterPlayer)
	{
		ShooterPlayer->TeamNumber = TeamNumber;
	}
}

void APlayerState_Base::CLIENT_UpdateColorOfSpawn_Implementation(UStaticMeshComponent* MeshToChangeColor, UMaterialInterface* MaterialChangeTo)
{
	if (MeshToChangeColor) 
	{
		MeshToChangeColor->SetMaterial(0, MaterialChangeTo);
	}

}

APlayerController_Base * APlayerState_Base::GetMyController()
{
	return MyController;
}

void APlayerState_Base::SetMyController(APlayerController_Base * SetController)
{
	MyController = SetController;
}

void APlayerState_Base::SetPlayerScore(float SetAmount)
{
	PlayerScore = SetAmount;
}

float APlayerState_Base::GetPlayerScore()
{
	return PlayerScore;
}

void APlayerState_Base::SetPlayerCurrency(float SetAmount)
{
	PlayerCurrency = SetAmount;
}

float APlayerState_Base::GetPlayerCurrency()
{
	return PlayerCurrency;
}

bool APlayerState_Base::SetPlayerReady(bool bShouldReady)
{
	bPlayerIsReady = bShouldReady;
	return bShouldReady;
}

uint8 APlayerState_Base::GetTeamNum() const
{
	return TeamNumber;
}

int32 APlayerState_Base::GetKills() const
{
	return NumKills;
}

int32 APlayerState_Base::GetDeaths() const
{
	return NumDeaths;
}

float APlayerState_Base::GetScore() const
{
	return Score;
}

int32 APlayerState_Base::GetNumBulletsFired() const
{
	return NumBulletsFired;
}

int32 APlayerState_Base::GetNumRocketsFired() const
{
	return NumRocketsFired;
}

bool APlayerState_Base::IsQuitter() const
{
	return bQuitter;
}

void APlayerState_Base::ScoreKill(APlayerState_Base* Victim, int32 Points)
{
	NumKills++;
	ScorePoints(Points);
}

void APlayerState_Base::ScoreDeath(APlayerState_Base* KilledBy, int32 Points)
{
	NumDeaths++;
	ScorePoints(Points);
}

void APlayerState_Base::ScorePoints(int32 Points)
{
	AMyGameState_Base* const MyGameState = GetWorld()->GetGameState<AMyGameState_Base>();
	if (MyGameState && TeamNumber >= 0)
	{
		//TODO Add Team Score
		/*if (TeamNumber >= MyGameState->TeamScores.Num())
		{
			MyGameState->TeamScores.AddZeroed(TeamNumber - MyGameState->TeamScores.Num() + 1);
		}

		MyGameState->TeamScores[TeamNumber] += Points;*/
	}

	Score += Points;
}

void APlayerState_Base::OnRep_PlayerStartLocation()
{

}

void APlayerState_Base::OnRep_CharacterSpawnPoint()
{
}

void APlayerState_Base::OnRep_MyController()
{
}

void APlayerState_Base::OnRep_PlayerScore()
{
}

void APlayerState_Base::OnRep_PlayerCurrency()
{
}

void APlayerState_Base::SetSpawnLocation(ASpawnPoint_Base* LocationToSet)
{
	CharacterSpawnPoint = LocationToSet;
}

ASpawnPoint_Base * APlayerState_Base::GetSpawnLocation()
{
	return CharacterSpawnPoint;
}

APlayerStart * APlayerState_Base::GetPlayerStartLocation()
{
	return PlayerStartLocation;
}

void APlayerState_Base::SetPlayerStartLocation(APlayerStart* LocationToSet)
{
	PlayerStartLocation = LocationToSet;
}

void APlayerState_Base::InformAboutKill_Implementation(class APlayerState_Base* KillerPlayerState, const UDamageType* KillerDamageType, class APlayerState_Base* KilledPlayerState)
{
	//id can be null for bots
	if (KillerPlayerState->UniqueId.IsValid())
	{
		//search for the actual killer before calling OnKill()	
		for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
		{
			APlayerController_Base* TestPC = Cast<APlayerController_Base>(*It);
			if (TestPC && TestPC->IsLocalController())
			{
				// a local player might not have an ID if it was created with CreateDebugPlayer.

				/*ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(TestPC->Player);
				TSharedPtr<const FUniqueNetId> LocalID = LocalPlayer->GetCachedUniqueNetId();
				if (LocalID.IsValid() && *LocalPlayer->GetCachedUniqueNetId() == *KillerPlayerState->UniqueId)
				{
					TestPC->OnKill();
				}*/
			}
		}
	}
}

void APlayerState_Base::BroadcastDeath_Implementation(class APlayerState_Base* KillerPlayerState, const UDamageType* KillerDamageType, class APlayerState_Base* KilledPlayerState)
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		// all local players get death messages so they can update their huds.
		APlayerController_Base* TestPC = Cast<APlayerController_Base>(*It);
		if (TestPC && TestPC->IsLocalController())
		{
			//TestPC->OnDeathMessage(KillerPlayerState, this, KillerDamageType);
		}
	}
}

void APlayerState_Base::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerState_Base, TeamNumber);
	DOREPLIFETIME(APlayerState_Base, NumKills);
	DOREPLIFETIME(APlayerState_Base, NumDeaths);
	DOREPLIFETIME(APlayerState_Base, PlayerStartLocation);
	DOREPLIFETIME(APlayerState_Base, CharacterSpawnPoint);
	DOREPLIFETIME(APlayerState_Base, MyController);
	DOREPLIFETIME(APlayerState_Base, PlayerScore);
	DOREPLIFETIME(APlayerState_Base, PlayerCurrency);
	DOREPLIFETIME(APlayerState_Base, bPlayerIsReady);

}

FString APlayerState_Base::GetShortPlayerName() const
{
	if (PlayerName.Len() > MAX_PLAYER_NAME_LENGTH)
	{
		return PlayerName.Left(MAX_PLAYER_NAME_LENGTH) + "...";
	}
	return PlayerName;
}


