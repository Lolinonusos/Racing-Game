// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseScreen.h"
#include "../Vehicle/Car.h"
#include "GameHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

bool UPauseScreen::Initialize() {
	Super::Initialize();

	if (ResumeButton) {
		ResumeButton->OnClicked.AddDynamic(this, &UPauseScreen::ClickResumeBtn);
	}
	if (OptionsButton) {
		OptionsButton->OnClicked.AddDynamic(this, &UPauseScreen::ClickOptionsBtn);
	}
	if (RestartButton) {
		RestartButton->OnClicked.AddDynamic(this, &UPauseScreen::ClickRestartBtn);
	}
	if (MenuButton) {
		MenuButton->OnClicked.AddDynamic(this, &UPauseScreen::ClickMenuBtn);
	}
	if (PauseMenuControlsButton) {
		PauseMenuControlsButton->OnClicked.AddDynamic(this, &UPauseScreen::ClickControlsBtn);
	}

	return true;
}

void UPauseScreen::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UPauseScreen::ClickResumeBtn() {
	if (!PauseMenuInstancePtr) {
		PauseMenuInstancePtr = Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}
	UGameplayStatics::PlaySound2D(GetWorld(), ClickingSound, PauseMenuInstancePtr->GetGameAudio(), 1.f, 0.f, nullptr, nullptr, true);
	UE_LOG(LogTemp, Warning, TEXT("RESUMING"))
	ACar* PauseCarPtr = Cast<ACar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	PauseCarPtr->bGameIsPaused = true;
	PauseCarPtr->PauseGame();
}

void UPauseScreen::ClickOptionsBtn() {
	if (!PauseMenuInstancePtr) {
		PauseMenuInstancePtr = Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}
	UGameplayStatics::PlaySound2D(GetWorld(), ClickingSound, PauseMenuInstancePtr->GetGameAudio(), 1.f, 0.f, nullptr, nullptr, true);
	Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD())->OpenOptionsMenu();
}

void UPauseScreen::ClickRestartBtn() {
	if (!PauseMenuInstancePtr) {
		PauseMenuInstancePtr = Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}
	UGameplayStatics::PlaySound2D(GetWorld(), ClickingSound, PauseMenuInstancePtr->GetGameAudio(), 1.f, 0.f, nullptr, nullptr, true);
	UGameplayStatics::OpenLevel(GetWorld(), "TheBigCheesus");
}

void UPauseScreen::ClickMenuBtn() {
	if (!PauseMenuInstancePtr) {
		PauseMenuInstancePtr = Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}
	UGameplayStatics::PlaySound2D(GetWorld(), ClickingSound, PauseMenuInstancePtr->GetGameAudio(), 1.f, 0.f, nullptr, nullptr, true);
	
	UGameplayStatics::OpenLevel(GetWorld(), "LVL_MainMenu");
}

void UPauseScreen::ClickControlsBtn() {
	if (!PauseMenuInstancePtr) {
		PauseMenuInstancePtr = Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}
	UGameplayStatics::PlaySound2D(GetWorld(), ClickingSound, PauseMenuInstancePtr->GetGameAudio(), 1.f, 0.f, nullptr, nullptr, true);
	Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD())->ShowControls();
}