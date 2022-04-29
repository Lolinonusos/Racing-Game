// Fill out your copyright notice in the Description page of Project Settings.


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
}

void AGameHUD::CloseOptionsMenuFromMain() {
	OptionsWidget->SetVisibility(ESlateVisibility::Hidden);
}

void AGameHUD::OpenPauseMenu() {
	PauseWidget->SetVisibility(ESlateVisibility::Visible);
}

void AGameHUD::ClosePauseMenu() {
	PauseWidget->SetVisibility(ESlateVisibility::Hidden);
}

