// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD_Base.h"
#include "PlayerController_Base.h"
#include "Runtime/Engine/Classes/Engine/Canvas.h"

AHUD_Base::AHUD_Base(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) 
{
	HommingTargetLocation = FVector(0.0f);
	bHommingTargetted = false;
	Pulse = 0.0f;
}

void AHUD_Base::BeginPlay() 
{
	Super::BeginPlay();
	StartPulse();
}

void AHUD_Base::DrawHUD() 
{
	Super::DrawHUD();
	FVector2D ScreenDimensions = FVector2D(Canvas->SizeX, Canvas->SizeY);
	if (bHommingTargetted)
	{
		DrawHommingTarget(HommingTargetLocation);
	}
}

void AHUD_Base::StartPulse_Implementation() {}

void AHUD_Base::DrawHommingTarget(FVector Location) 
{
	const FVector ProjectedLocation = Project(Location);
	const float OffsetX = Canvas->SizeX * 0.01f;
	const float OffsetY = Canvas->SizeX * 0.01f;
	const float LineThickness = 1.0f;
	FLinearColor LineColor;
	LineColor.G = 1.0f;
	LineColor.A = Pulse;//Pulse not working for some reason

	DrawLine(ProjectedLocation.X + OffsetX, ProjectedLocation.Y+ OffsetY, ProjectedLocation.X - OffsetX, ProjectedLocation.Y - OffsetY, LineColor, LineThickness);
	DrawLine(ProjectedLocation.X + OffsetX, ProjectedLocation.Y - OffsetY, ProjectedLocation.X - OffsetX, ProjectedLocation.Y + OffsetY, LineColor, LineThickness);
	DrawLine(ProjectedLocation.X - OffsetX, ProjectedLocation.Y + OffsetY, ProjectedLocation.X - OffsetX, ProjectedLocation.Y - OffsetY, LineColor, LineThickness);
	DrawLine(ProjectedLocation.X - OffsetX, ProjectedLocation.Y - OffsetY, ProjectedLocation.X + OffsetX, ProjectedLocation.Y - OffsetY, LineColor, LineThickness);
	DrawLine(ProjectedLocation.X + OffsetX, ProjectedLocation.Y - OffsetY, ProjectedLocation.X + OffsetX, ProjectedLocation.Y + OffsetY, LineColor, LineThickness);
	DrawLine(ProjectedLocation.X + OffsetX, ProjectedLocation.Y + OffsetY, ProjectedLocation.X - OffsetX, ProjectedLocation.Y + OffsetY, LineColor, LineThickness);
}

