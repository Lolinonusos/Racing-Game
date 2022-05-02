// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuScreen.h"
#include "Components/Button.h"
#include "GameHUD.h"

bool UMainMenuScreen::Initialize() {
	Super::Initialize();

	if (MainMenuStartGameButton) {
		MainMenuStartGameButton->OnClicked.AddDynamic(this, &UMainMenuScreen::ClickStartGame);
	}
	if (MainMenuOptionsButton) {
		MainMenuOptionsButton->OnClicked.AddDynamic(this, &UMainMenuScreen::ClickOptions);
	}
	if (MainMenuExitButton) {
		MainMenuExitButton->OnClicked.AddDynamic(this, &UMainMenuScreen::ClickExit);
	}
	
	return true;
}

void UMainMenuScreen::ClickStartGame() {
	UGameplayStatics::PlaySound2D(GetWorld(), MainMenuClickSound, 1, 1, 0, nullptr, nullptr, true);
	PlaySound(MainMenuClickSound);
	UGameplayStatics::OpenLevel(GetWorld(), "LVL_LevelSelect");
}

void UMainMenuScreen::ClickOptions() {
	UGameplayStatics::PlaySound2D(GetWorld(), MainMenuClickSound, 1, 1, 0, nullptr, nullptr, true);
	Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD())->OpenOptionsMenuFromMain();
}

void UMainMenuScreen::ClickExit() {
	PlaySound(MainMenuClickSound);
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
}