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
	
	
	
	return true;
}

void UMainMenuScreen::ClickStartGame() {
	UGameplayStatics::OpenLevel(GetWorld(), "LVL_LevelSelect");
	if (!MainMenuInstancePtr) {
		MainMenuInstancePtr = Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}
	UGameplayStatics::PlaySound2D(GetWorld(), MainMenuClickSound, MainMenuInstancePtr->GetGameAudio(), 1.f, 0.f, nullptr, nullptr, true);
}

void UMainMenuScreen::ClickOptions() {
	if (!MainMenuHUDPtr) {
		MainMenuHUDPtr = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	}
	MainMenuHUDPtr->OpenOptionsMenuFromMain();
	if (!MainMenuInstancePtr) {
		MainMenuInstancePtr = Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}
	UGameplayStatics::PlaySound2D(GetWorld(), MainMenuClickSound, MainMenuInstancePtr->GetGameAudio(), 1.f, 0.f, nullptr, nullptr, true);
}

void UMainMenuScreen::ClickExit() {
	if (!MainMenuInstancePtr) {
		MainMenuInstancePtr = Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
	UGameplayStatics::PlaySound2D(GetWorld(), MainMenuClickSound, MainMenuInstancePtr->GetGameAudio(), 1.f, 0.f, nullptr, nullptr, true);
}

void UMainMenuScreen::ClickControlsButton() {
	if (!MainMenuHUDPtr) {
		MainMenuHUDPtr = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0 )->GetHUD());
	}
	MainMenuHUDPtr->ShowControls();
	if (!MainMenuInstancePtr) {
		MainMenuInstancePtr = Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}
	MainMenuInstancePtr->bHasSeenControls = true;
	UGameplayStatics::PlaySound2D(GetWorld(), MainMenuClickSound, MainMenuInstancePtr->GetGameAudio(), 1.f, 0.f, nullptr, nullptr, true);
}
