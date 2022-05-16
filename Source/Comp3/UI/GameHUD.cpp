// Fill out your copyright notice in the Description page of Project Settings.

// THIS DOCUMENT WAS WRITTEN BY JOACHIM

#include "GameHUD.h"

AGameHUD::AGameHUD() {
	
}

void AGameHUD::BeginPlay() {
	Super::BeginPlay();

	if (PauseWidgetClass) {
		PauseWidget = CreateWidget<UPauseScreen>(GetWorld(), PauseWidgetClass);
		if (PauseWidget) {
			PauseWidget->AddToViewport();
			PauseWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	if (OptionsWidgetClass) {
		OptionsWidget = CreateWidget<UOptionsMenu>(GetWorld(), OptionsWidgetClass);
		if (OptionsWidget) {
			OptionsWidget->AddToViewport();
			OptionsWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (LevelSelectWidgetClass) {
		LevelSelectWidget = CreateWidget<ULevelSelectWidget>(GetWorld(), LevelSelectWidgetClass);
		if (LevelSelectWidget) {
			LevelSelectWidget->AddToViewport();
			if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "LVL_LevelSelect") {
				LevelSelectWidget->SetVisibility(ESlateVisibility::Visible);
				UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
			}
			else {
				LevelSelectWidget->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}

	if (FocusedLevelSelectWidgetClass) {
		FocusedLevelSelectWidget = CreateWidget<UFocusedLevelSelectHUD>(GetWorld(), FocusedLevelSelectWidgetClass);
		if (FocusedLevelSelectWidget) {
			FocusedLevelSelectWidget->AddToViewport();
			FocusedLevelSelectWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (TimeTrialHUDWidgetClass) {
		TimeTrialHUDWidget = CreateWidget<UTimeTrialHUD>(GetWorld(), TimeTrialHUDWidgetClass);
		if (TimeTrialHUDWidget) {
			TimeTrialHUDWidget->AddToViewport();
			TimeTrialHUDWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (FixedPlayerHUDWidgetClass) {
		FixedPlayerHUDWidget = CreateWidget<UFixedPlayerHUD>(GetWorld(), FixedPlayerHUDWidgetClass);
		if (FixedPlayerHUDWidget) {
			FixedPlayerHUDWidget->AddToViewport();
			FixedPlayerHUDWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (FinishedRaceScreenWidgetClass) {
		FinishedRaceScreenWidget = CreateWidget<UFinishedRaceScreen>(GetWorld(), FinishedRaceScreenWidgetClass);
		if (FinishedRaceScreenWidget) {
			FinishedRaceScreenWidget->AddToViewport();
			FinishedRaceScreenWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (MainMenuWidgetClass) {
		MainMenuWidget = CreateWidget<UMainMenuScreen>(GetWorld(), MainMenuWidgetClass);
		if (MainMenuWidget) {
			MainMenuWidget->AddToViewport();
			MainMenuWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (ControlsScreenWidgetClass) {
		ControlsScreenWidget = CreateWidget<UControlsScreen>(GetWorld(), ControlsScreenWidgetClass);
		if (ControlsScreenWidget) {
			ControlsScreenWidget->AddToViewport();
			ControlsScreenWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "Test" || UGameplayStatics::GetCurrentLevelName(GetWorld()) == "FeatureDisplay") {
		if (HUDInstancePtr->ChosenGameModeToPlay == "Shooter") {
			SetupHUDForShooterMode();
		}
		if (HUDInstancePtr->ChosenGameModeToPlay == "Time") {
			SetupHUDForTimeTrialMode();
			GetWorld()->GetTimerManager().SetTimer(TimeTrialTimerHandle, this, &AGameHUD::UpdateTimer, 0.01f, true, 4.f);
			GetWorld()->GetTimerManager().SetTimer(SecondsSurvivedHandle, this, &AGameHUD::IncreaseSurvivedSeconds, 0.01f, true, 4.f);
		}
	}
	
	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "LVL_MainMenu") {
		ShowMainMenu();
	}
}

void AGameHUD::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	if (OptionsWidget->Visibility == ESlateVisibility::Visible) {
		OptionsWidget->UpdateSliderPercentage();
	}
}

void AGameHUD::DrawHUD() {
	Super::DrawHUD();
}


void AGameHUD::UpdateSliderPercentage() {
	OptionsWidget->UpdateSliderPercentage();
}

void AGameHUD::OpenOptionsMenu() {
	OptionsWidget->SetVisibility(ESlateVisibility::Visible);
	PauseWidget->SetVisibility(ESlateVisibility::Hidden);
}

void AGameHUD::CloseOptionsMenu() {
	OptionsWidget->SetVisibility(ESlateVisibility::Hidden);
	PauseWidget->SetVisibility(ESlateVisibility::Visible);
}

void AGameHUD::OpenOptionsMenuFromMain() {
	OptionsWidget->SetVisibility(ESlateVisibility::Visible);
	MainMenuWidget->SetVisibility(ESlateVisibility::Hidden);
}

void AGameHUD::CloseOptionsMenuFromMain() {
	OptionsWidget->SetVisibility(ESlateVisibility::Hidden);
	MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
}

void AGameHUD::OpenPauseMenu() {
	PauseWidget->SetVisibility(ESlateVisibility::Visible);
	TimeTrialHUDWidget->SetVisibility((ESlateVisibility::Hidden));
	FixedPlayerHUDWidget->SetVisibility(ESlateVisibility::Hidden);
}

void AGameHUD::ClosePauseMenu() {
	PauseWidget->SetVisibility(ESlateVisibility::Hidden);
	if (HUDInstancePtr->ChosenGameModeToPlay == "Racing") {
		FixedPlayerHUDWidget->SetVisibility(ESlateVisibility::Visible);
	} else {
		TimeTrialHUDWidget->SetVisibility(ESlateVisibility::Visible);	
	}
}

void AGameHUD::FocusOnPlanet() {
	LevelSelectWidget->SetVisibility(ESlateVisibility::Hidden);
	FocusedLevelSelectWidget->SetVisibility(ESlateVisibility::Visible);
	FocusedLevelSelectWidget->ChangeGameModeDescription();
}

void AGameHUD::LeaveFocusOnPlanet() {
	LevelSelectWidget->SetVisibility(ESlateVisibility::Visible);
	FocusedLevelSelectWidget->SetVisibility(ESlateVisibility::Hidden);
}

FString AGameHUD::GetGameModeSelected() {
	if (FocusedLevelSelectWidget) {
		FString a = FocusedLevelSelectWidget->SelectedGameMode;
		return a;
	}
	return "";
}

void AGameHUD::SetupHUDForShooterMode() {
	FixedPlayerHUDWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void AGameHUD::SetupHUDForTimeTrialMode() {
	TimeTrialHUDWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void AGameHUD::UpdateTimer() {
	TimeTrialHUDWidget->UpdateTimer();
	TimeTrialHUDWidget->DecreaseTime();
}

void AGameHUD::ShowFinishScreen() {
	FinishedRaceScreenWidget->SetVisibility(ESlateVisibility::Visible);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
}

void AGameHUD::ShowMainMenu() {
	MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
}

void AGameHUD::ShowControls() {
	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "LVL_MainMenu") {
		ControlsScreenWidget->SetVisibility(ESlateVisibility::Visible);
		ControlsScreenWidget->ChangeButtonText("Return to Main Menu");
		MainMenuWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	else {
		ControlsScreenWidget->SetVisibility(ESlateVisibility::Visible);
		ControlsScreenWidget->ChangeButtonText("Return to Pause Menu");
		PauseWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AGameHUD::HideControls() {
	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "LVL_MainMenu") {
		ControlsScreenWidget->SetVisibility(ESlateVisibility::Hidden);
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		ControlsScreenWidget->SetVisibility(ESlateVisibility::Hidden);
		PauseWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

int AGameHUD::GetTimeTrialScore() {
	return TimeTrialHUDWidget->Score;
}

int AGameHUD::GetPickupScore() {
	return TimeTrialHUDWidget->PickupsCollected;
}

void AGameHUD::FinishTimeTrialMode() {
	GetWorld()->GetTimerManager().ClearTimer(TimeTrialTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer((SecondsSurvivedHandle));
	FinishedRaceScreenWidget->CalculateTimeTrialScore();
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	ShowFinishScreen();
}

void AGameHUD::IncreaseTime() {
	TimeTrialHUDWidget->AddTime(10);
}

void AGameHUD::IncreasePickupCount() {
	TimeTrialHUDWidget->PickupsCollected++;
	UE_LOG(LogTemp, Warning, TEXT("PICKUPS COLLECTED: %d"),TimeTrialHUDWidget->PickupsCollected)
}

void AGameHUD::IncreaseSurvivedSeconds() {
	TimeTrialHUDWidget->IncreaseTimeScore();
}

float AGameHUD::GetVolumeMultiplier() {
	AudioMultiplier = OptionsWidget->GetVolume();
	return AudioMultiplier;
}

// Linus mode
int AGameHUD::GetScoreTimeTrial()
{
	return FinishedRaceScreenWidget->CalculateTimeTrialScore();
}
