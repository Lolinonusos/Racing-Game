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
	AudioSlider->SetValue(Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetGameAudio());
	int AudioPercentage = AudioSlider->GetValue() * 100;
	FString OutputAudioPercentage = FString::FromInt(AudioPercentage);
	OutputAudioPercentage.Append("%");
	AudioPercentText->SetText(FText::FromString(OutputAudioPercentage));
	GetVolume();
}

void UOptionsMenu::ClickReturnBtn() {
	AGameHUD* OptionsHUDPtr = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	URacingGameInstance* OptionsInstancePtr = Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "LVL_MainMenu") {
		OptionsHUDPtr->GetVolumeMultiplier();
		OptionsHUDPtr->CloseOptionsMenuFromMain();
		UGameplayStatics::PlaySound2D(GetWorld(), ReturnButtonSound, OptionsInstancePtr->GetGameAudio(), 1.f, 0.f, nullptr, nullptr, true);
	}
	else {
		OptionsHUDPtr->GetVolumeMultiplier();
		OptionsHUDPtr->CloseOptionsMenu();
		UGameplayStatics::PlaySound2D(GetWorld(), ReturnButtonSound, OptionsInstancePtr->GetGameAudio(), 1.f, 0.f, nullptr, nullptr, true);
	}
}

float UOptionsMenu::GetVolume() {
	AudioSlider->SetValue(Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetGameAudio());
	Volume = AudioSlider->GetValue();
	return  Volume;
}