// Fill out your copyright notice in the Description page of Project Settings.


#include "FocusedLevelSelectHUD.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UFocusedLevelSelectHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("HELOOOOO"));
	
	FocusedLevelName->SetText(FText::FromString(FocusedLevelSelectPtr->Levels[FocusedLevelSelectPtr->RotationNumber].PlanetName));
	
	if (!bGameModeSelected) {
		PlayButtonText->SetText(FText::FromString("Select a game mode"));
	}
	else {
		PlayButtonText->SetText(FText::FromString("Start Game"));
	}
}