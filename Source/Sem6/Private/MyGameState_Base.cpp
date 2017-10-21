// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameState_Base.h"
#include "PlayerState_Base.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

AMyGameState_Base::AMyGameState_Base(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	WiningScore = 50.0f;
}

void AMyGameState_Base::MULTICAST_PlaySoundAtLocation_Implementation(USoundBase * Sound, FVector Location, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation * AttenuationSettings, USoundConcurrency * ConcurrencySettings)
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, Location, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings);
	return;
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
