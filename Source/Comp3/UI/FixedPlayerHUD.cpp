// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedPlayerHUD.h"
#include "Components/TextBlock.h"

void UFixedPlayerHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

	// This HUD class is for things like laps and checkpoint number
	// This HUD will be fixed to the screen, meaning it will not change based on environment


	if (FixedHUDPtr) {
		int CurrentCheckpoints = FixedHUDPtr->CheckPointsReached;
		int LevelsTotalCheckpoints = FixedHUDPtr->TotalCheckPoints;
		int LevelsTotalLaps = FixedHUDPtr->TotalLaps;
		int CurrentLaps = FixedHUDPtr->LapsCleared;

		FString CheckpointTextOutput = "CPs: ";
		CheckpointTextOutput.Append(FString::FromInt(CurrentCheckpoints));
		CheckpointTextOutput.Append(" / ");
		CheckpointTextOutput.Append(FString::FromInt(LevelsTotalCheckpoints));

		FString LapsTextOutput = "Laps: ";
		LapsTextOutput.Append(FString::FromInt(CurrentLaps));
		LapsTextOutput.Append(" / ");
		LapsTextOutput.Append(FString::FromInt(LevelsTotalLaps));

		Laps->SetText(FText::FromString(LapsTextOutput));
		Checkpoints->SetText(FText::FromString(CheckpointTextOutput));
	}
	else { return; }
}