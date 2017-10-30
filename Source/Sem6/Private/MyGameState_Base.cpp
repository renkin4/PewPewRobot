// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameState_Base.h"
#include "PlayerState_Base.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

AMyGameState_Base::AMyGameState_Base(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	WiningScore = 50.0f;
	PrimaryActorTick.bCanEverTick = false;

}

void AMyGameState_Base::CheckScore_Implementation()
{
	TArray<APlayerState*> PArray = PlayerArray;
	APlayerState_Base* PState;
	float PScore;
	/*Check if anyone is winning*/
	for (int x = 0; x < PArray.Num(); x++) 
	{
		PState = Cast<APlayerState_Base>(PArray[x]);
		if (PState) 
		{
			PScore = PState->GetPlayerScore();
			if (PScore >= WiningScore) 
			{
				OnWin(PState);
			}
		}
	}	
}

void AMyGameState_Base::OnWin_Implementation(APlayerState_Base* PState)
{
	GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Green, FString::Printf(TEXT("Winner is :: %s"), *PState->PlayerName));
	/*TODO Unpossessed All Pawn that exist in the world and spawn the UI*/
}

void AMyGameState_Base::MULTICAST_DestroyActor_Implementation(AActor * ActorToDestroy)
{
	ActorToDestroy->Destroy();
}

void AMyGameState_Base::DestroyingActor_Implementation(AActor * ActorToDestroy)
{
	if (!ActorToDestroy->IsPendingKill()) 
	{
		MULTICAST_DestroyActor(ActorToDestroy);
	}
}

void AMyGameState_Base::OnJoinTeam(APlayerState_Base* PS, uint8 TeamToJoin)
{
	PS->SetTeamNum(TeamToJoin);
	MULTICAST_OnJoinTeam(PS, TeamToJoin);
}

bool AMyGameState_Base::UpdateReadyStatus(APlayerState_Base* PS)
{
	MULTICAST_UpdateReadyStatus(PS);
	return PS->GetIsPlayerReady();
}

void AMyGameState_Base::OnLeaveTeam(uint8 TeamNum)
{
	MULTICAST_OnLeaveTeam(TeamNum);
}

bool AMyGameState_Base::CheckEveryoneReady(APlayerState_Base* ServerPS)
{
	bool bIsEveryoneReady = true;
	TArray<APlayerState*> PSArray = PlayerArray;
	APlayerState_Base* PS;
	for (APlayerState* PState: PSArray)
	{
		PS = Cast<APlayerState_Base>(PState);
		if (PS && PS != ServerPS) 
		{
			if (!PS->GetIsPlayerReady())
			{
				bIsEveryoneReady = PS->GetIsPlayerReady();
				break;
			}
		}
	}
	return bIsEveryoneReady;
}

void AMyGameState_Base::MULTICAST_OnLeaveTeam_Implementation(uint8 TeamNum)
{
	DelegateLeaveTeam.Broadcast(TeamNum);
}

void AMyGameState_Base::MULTICAST_UpdateReadyStatus_Implementation(APlayerState_Base* PS)
{
	UpdateRSDelegate.Broadcast(PS);
}

void AMyGameState_Base::MULTICAST_OnJoinTeam_Implementation(APlayerState_Base* PS, uint8 TeamToJoin)
{
	DelegateJoinTeam.Broadcast(PS,TeamToJoin);
}
