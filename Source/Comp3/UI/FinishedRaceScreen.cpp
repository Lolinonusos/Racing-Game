// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishedRaceScreen.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "GameHUD.h"
#include "Kismet/GameplayStatics.h"

// THIS DOCUMENT WAS WRITTEN BY JOACHIM

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

int UFinishedRaceScreen::CalculateTimeTrialScore() {
	int SecondScore = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD())->GetTimeTrialScore();
	SecondScore *= 5;

	int PickupsScore = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD())->GetPickupScore();
	PickupsScore *= 50;

	int CheckpointsScore = 0;
	
	// Linus worked here
	AComp3GameModeBase* GameModePtr = Cast<AComp3GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	
	CheckpointsScore = (200 * GameModePtr->CheckpointScoreMultiplier);
	FinalScore = SecondScore + PickupsScore + CheckpointsScore;

	return FinalScore;
	
}

void UFinishedRaceScreen::OutPutFinalScore()
{
	// Back to Joachim
	FString TimeTrialOutput = "Your Score: ";
	TimeTrialOutput.Append(FString::FromInt(FinalScore));
	TimeTrialText->SetText(FText::FromString(TimeTrialOutput));
}
