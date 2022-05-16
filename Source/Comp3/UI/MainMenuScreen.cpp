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
	if (MainMenuControlsButton) {
		MainMenuControlsButton->OnClicked.AddDynamic(this, &UMainMenuScreen::ClickControlsButton);
	}
	if (!MainMenuHUDPtr) {
		MainMenuHUDPtr = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0 )->GetHUD());
	}
	if (!MainMenuInstancePtr) {
		MainMenuInstancePtr = Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}
	
	return true;
}

void UMainMenuScreen::ClickStartGame() {
	UGameplayStatics::OpenLevel(GetWorld(), "LVL_LevelSelect");
	UGameplayStatics::PlaySound2D(GetWorld(), MainMenuClickSound, MainMenuInstancePtr->GetGameAudio(), 1.f, 0.f, nullptr, nullptr, true);
}

void UMainMenuScreen::ClickOptions() {
	MainMenuHUDPtr->OpenOptionsMenuFromMain();
	UGameplayStatics::PlaySound2D(GetWorld(), MainMenuClickSound, MainMenuInstancePtr->GetGameAudio(), 1.f, 0.f, nullptr, nullptr, true);
}

void UMainMenuScreen::ClickExit() {
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
	UGameplayStatics::PlaySound2D(GetWorld(), MainMenuClickSound, MainMenuInstancePtr->GetGameAudio(), 1.f, 0.f, nullptr, nullptr, true);
}

void UMainMenuScreen::ClickControlsButton() {
	MainMenuHUDPtr->ShowControls();
	UGameplayStatics::PlaySound2D(GetWorld(), MainMenuClickSound, MainMenuInstancePtr->GetGameAudio(), 1.f, 0.f, nullptr, nullptr, true);
}
