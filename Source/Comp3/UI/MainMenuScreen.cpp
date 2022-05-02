// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuScreen.h"
#include "Components/Button.h"
#include "GameHUD.h"

bool UMainMenuScreen::Initialize() {
	Super::Initialize();

	StarGameButton->OnClicked.AddDynamic(this, &UMainMenuScreen::ClickStartGame);
	OptionsButton->OnClicked.AddDynamic(this, &UMainMenuScreen::ClickOptions);
	ExitButton->OnClicked.AddDynamic(this, &UMainMenuScreen::ClickExit);

	return true;
}

void UMainMenuScreen::ClickStartGame() {
	UGameplayStatics::OpenLevel(GetWorld(), "LVL_LevelSelect");
}

void UMainMenuScreen::ClickOptions() {
	Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD())->OpenOptionsMenuFromMain();
}

void UMainMenuScreen::ClickExit() {
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
}