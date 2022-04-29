// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionsMenu.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Slider.h"

void UOptionsMenu::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UOptionsMenu::UpdateSliderPercentage() {
	int AudioPercentage = AudioSlider->GetValue() * 100;
	FString OutputAudioPercentage = FString::FromInt(AudioPercentage);
	OutputAudioPercentage.Append("%");
	AudioPercentText->SetText(FText::FromString(OutputAudioPercentage));
	UE_LOG(LogTemp, Warning, TEXT("IN THE UPDATESLIDER FUNCTION"));
}
