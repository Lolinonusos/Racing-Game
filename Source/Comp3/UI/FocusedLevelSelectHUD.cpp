// Fill out your copyright notice in the Description page of Project Settings.


#include "FocusedLevelSelectHUD.h"
#include "Components/TextBlock.h"
#include "GameHUD.h"
#include "../Game-Logic/RacingGameInstance.h"
#include "Components/Button.h"

bool UFocusedLevelSelectHUD::Initialize() {
	Super::Initialize();

	if (RacingModeButton) {
		RacingModeButton->OnClicked.AddDynamic(this, &UFocusedLevelSelectHUD::ClickRacingModeBtn);
	}
	if (TimeTrialModeButton) {
		TimeTrialModeButton->OnClicked.AddDynamic(this, &UFocusedLevelSelectHUD::ClickTimeTrialModeBtn);
	}
	if (BackButton) {
		BackButton->OnClicked.AddDynamic(this, &UFocusedLevelSelectHUD::ClickBackButton);
	}
	if (PlayButton) {
		PlayButton->OnClicked.AddDynamic(this, &UFocusedLevelSelectHUD::ClickPlayButton);
	}

	return true;
}

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

void UFocusedLevelSelectHUD::ClickRacingModeBtn() {
	URacingGameInstance* InstancePtr1 = Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	InstancePtr1->ChosenGameModeToPlay = "Racing";
	bGameModeSelected = true;
}

void UFocusedLevelSelectHUD::ClickTimeTrialModeBtn() {
	URacingGameInstance* InstancePtr2 = Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	InstancePtr2->ChosenGameModeToPlay = "Time";
	bGameModeSelected = true;
}

void UFocusedLevelSelectHUD::ClickBackButton() {
	if (!FocusedLevelSelectPtr->bIsEnteringFocus) {
		Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD())->LeaveFocusOnPlanet();
		FocusedLevelSelectPtr->bIsLeavingFocus = true;
	}
}

void UFocusedLevelSelectHUD::ClickPlayButton() {
	if (bGameModeSelected) {
		if (FocusedLevelSelectPtr->Levels[FocusedLevelSelectPtr->RotationNumber].PlanetName == "The Big Cheesus") {
			UGameplayStatics::OpenLevel(GetWorld(), "Test");
		}
	}
}
