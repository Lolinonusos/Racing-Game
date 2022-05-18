// Fill out your copyright notice in the Description page of Project Settings.


#include "FocusedLevelSelectHUD.h"
#include "Components/TextBlock.h"
#include "GameHUD.h"
#include "../Game-Logic/RacingGameInstance.h"
#include "Components/Button.h"

bool UFocusedLevelSelectHUD::Initialize() {
	Super::Initialize();

	if (ShooterModeButton) {
		ShooterModeButton->OnClicked.AddDynamic(this, &UFocusedLevelSelectHUD::ClickShooterModeBtn);
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
	
	FocusedLevelName->SetText(FText::FromString(FocusedLevelSelectPtr->Levels[FocusedLevelSelectPtr->RotationNumber].PlanetName));
	
	if (!bGameModeSelected) {
		PlayButtonText->SetText(FText::FromString("Select a game mode"));
	}
	else {
		PlayButtonText->SetText(FText::FromString("Start Game"));
	}
}

void UFocusedLevelSelectHUD::ClickShooterModeBtn() {
	if (!FocusedLevelSelectInstancePtr) {
		FocusedLevelSelectInstancePtr = Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}
	FocusedLevelSelectInstancePtr->ChosenGameModeToPlay = "Shooter";
	ChangeGameModeDescription();
	bGameModeSelected = true;
	UGameplayStatics::PlaySound2D(GetWorld(), FocusedClickSelectSound, FocusedLevelSelectInstancePtr->GetGameAudio(), 1.f, 0.f, nullptr, nullptr, true);
}

void UFocusedLevelSelectHUD::ClickTimeTrialModeBtn() {
	if (!FocusedLevelSelectInstancePtr) {
		FocusedLevelSelectInstancePtr = Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}
	FocusedLevelSelectInstancePtr->ChosenGameModeToPlay = "Time";
	ChangeGameModeDescription();
	bGameModeSelected = true;
	UGameplayStatics::PlaySound2D(GetWorld(), FocusedClickSelectSound, FocusedLevelSelectInstancePtr->GetGameAudio(), 1.f, 0.f, nullptr, nullptr, true);
}

void UFocusedLevelSelectHUD::ClickBackButton() {
	if (!FocusedLevelSelectPtr->bIsEnteringFocus) {
		Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD())->LeaveFocusOnPlanet();
		FocusedLevelSelectPtr->bIsLeavingFocus = true;
		if (!FocusedLevelSelectInstancePtr) {
			FocusedLevelSelectInstancePtr = Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		}
		UGameplayStatics::PlaySound2D(GetWorld(), FocusedClickSelectSound, FocusedLevelSelectInstancePtr->GetGameAudio(), 1.f, 0.f, nullptr, nullptr, true);
	}
}

void UFocusedLevelSelectHUD::ClickPlayButton() {
	if (bGameModeSelected) {
		if (FocusedLevelSelectPtr->Levels[FocusedLevelSelectPtr->RotationNumber].PlanetName == "The Big Cheesus") {
			UGameplayStatics::OpenLevel(GetWorld(), "TheBigCheesus");
		}
		if (FocusedLevelSelectPtr->Levels[FocusedLevelSelectPtr->RotationNumber].PlanetName == "Play Test") {
			UGameplayStatics::OpenLevel(GetWorld(), "FeatureDisplay");
		}
		if (!FocusedLevelSelectInstancePtr) {
			FocusedLevelSelectInstancePtr = Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		}
		UGameplayStatics::PlaySound2D(GetWorld(), FocusedClickSelectSound, FocusedLevelSelectInstancePtr->GetGameAudio(), 1.f, 0.f, nullptr, nullptr, true);
	}
}

void UFocusedLevelSelectHUD::ChangeGameModeDescription() {
	if (Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->ChosenGameModeToPlay == "Shooter") {
		DescriptionNameText->SetText(FText::FromString("Shooter Mode"));
		DescriptionText->SetText(FText::FromString("Be the first to reach the finish line!\nShoot down your foes to gain points!"));
	}
	else  if (Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->ChosenGameModeToPlay == "Time") {
		DescriptionNameText->SetText(FText::FromString("Time Trial Mode"));
		DescriptionText->SetText(FText::FromString("Drive for as long as possible against time!\nGo through checkpoints and collect tokens to get\nmore time!"));
	}
	else {
		DescriptionNameText->SetText(FText::FromString("Select a gamemode"));
		DescriptionText->SetText(FText::FromString("Select a gamemode to view more information."));
	}
}
