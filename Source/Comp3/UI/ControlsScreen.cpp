// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlsScreen.h"
#include "Components/Button.h"
#include "Components/Textblock.h"
#include "GameHUD.h"

bool UControlsScreen::Initialize() {
	Super::Initialize();

	if (ControlsReturnButton) {
		ControlsReturnButton->OnClicked.AddDynamic(this, &UControlsScreen::ClickedControlsReturnBtn);
	}
	
	return true;
}

void UControlsScreen::ClickedControlsReturnBtn() {
	UWorld* ControlsWorld = GetWorld();

	if (ControlsWorld) {
		URacingGameInstance* ControlsInstancePtr = Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(ControlsWorld));
		if (ControlsInstancePtr)
		{
			UGameplayStatics::PlaySound2D(ControlsWorld, ControlsToMenuReturnSound, ControlsInstancePtr->GetGameAudio(), 1.f, 0.f, nullptr, nullptr, true);
			Cast<AGameHUD>(UGameplayStatics::GetPlayerController(ControlsWorld, 0)->GetHUD())->HideControls();
		}
	}
	
	
	
}

void UControlsScreen::ChangeButtonText(FString NewText) {
	ControlsReturnButtonText->SetText(FText::FromString(NewText));
}
