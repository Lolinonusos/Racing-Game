// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlsScreen.h"
#include "Components/Button.h"
#include "GameHUD.h"

bool UControlsScreen::Initialize() {
	Super::Initialize();

	if (ControlsReturnButton) {
		ControlsReturnButton->OnClicked.AddDynamic(this, &UControlsScreen::ClickedControlsReturnBtn);
	}
	
	return true;
}

void UControlsScreen::ClickedControlsReturnBtn() {
	Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD())->HideControls();
}