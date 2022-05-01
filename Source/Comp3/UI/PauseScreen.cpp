// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseScreen.h"
#include "Components/TextBlock.h"
#include "../Vehicle/Car.h"
#include "GameHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

bool UPauseScreen::Initialize() {
	Super::Initialize();

	ResumeButton->OnClicked.AddDynamic(this, &UPauseScreen::ClickResumeBtn);
	OptionsButton->OnClicked.AddDynamic(this, &UPauseScreen::ClickOptionsBtn);
	RestartButton->OnClicked.AddDynamic(this, &UPauseScreen::ClickRestartBtn);
	MenuButton->OnClicked.AddDynamic(this, &UPauseScreen::ClickMenuBtn);
	
	return true;
}

void UPauseScreen::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UPauseScreen::ClickResumeBtn() {
	ACar* PauseCarPtr = Cast<ACar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	PauseCarPtr->bGameIsPaused = true;
	PauseCarPtr->PauseGame();
}

void UPauseScreen::ClickOptionsBtn() {
	Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD())->OpenOptionsMenu();
}

void UPauseScreen::ClickRestartBtn() {
	UGameplayStatics::OpenLevel(GetWorld(), "Test");
}

void UPauseScreen::ClickMenuBtn() {
	UGameplayStatics::OpenLevel(GetWorld(), "LVL_MainMenu");
}
