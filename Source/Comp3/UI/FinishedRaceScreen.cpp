// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishedRaceScreen.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

bool UFinishedRaceScreen::Initialize() {
	Super::Initialize();

	if (RestartButton) {
		RestartButton->OnClicked.AddDynamic(this, &UFinishedRaceScreen::FinishClickRestartBtn);
	}
	if (MainMenuButton) {
		MainMenuButton->OnClicked.AddDynamic(this, &UFinishedRaceScreen::FinishClickMainMenuBtn);
	}
	

	return true;
}

void UFinishedRaceScreen::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UFinishedRaceScreen::FinishClickRestartBtn() {
	UGameplayStatics::OpenLevel(GetWorld(), FName(UGameplayStatics::GetCurrentLevelName(GetWorld())));
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void UFinishedRaceScreen::FinishClickMainMenuBtn() {
	UGameplayStatics::OpenLevel(GetWorld(), "LVL_MainMenu");
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}
