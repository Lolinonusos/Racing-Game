// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionsMenu.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "GameHUD.h"
#include "Components/Slider.h"

bool UOptionsMenu::Initialize() {
	Super::Initialize();
	
	if (ReturnButton) {
		ReturnButton->OnClicked.AddDynamic(this, &UOptionsMenu::ClickReturnBtn);
	}

	return true;
}

void UOptionsMenu::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UOptionsMenu::UpdateSliderPercentage() {
	int AudioPercentage = AudioSlider->GetValue() * 100;
	FString OutputAudioPercentage = FString::FromInt(AudioPercentage);
	OutputAudioPercentage.Append("%");
	AudioPercentText->SetText(FText::FromString(OutputAudioPercentage));
}

void UOptionsMenu::ClickReturnBtn() {
	AGameHUD* OptionsHUDPtr = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "LVL_MainMenu") {
		OptionsHUDPtr->CloseOptionsMenuFromMain();
	}
	else {
		OptionsHUDPtr->CloseOptionsMenu();
	}
}
