// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeTrialHUD.h"
#include "Components/TextBlock.h"



void UTimeTrialHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UTimeTrialHUD::IncreaseTime() {
	if (MilliSeconds + 1 < 100) {
		MilliSeconds++;
	}
	else {
		MilliSeconds = 0;
		if (Seconds + 1 < 60) {
			Seconds++;
		}
		else {
			Seconds = 0;
			Minutes++;
		}
	}

	if (MilliSeconds < 10) {
		MilliSecondsOutput = "0";
		MilliSecondsOutput.Append(FString::FromInt(MilliSeconds));
	}
	else {
		MilliSecondsOutput = FString::FromInt(MilliSeconds);
	}

	if (Seconds < 10) {
		SecondsOutput = "0";
		SecondsOutput.Append(FString::FromInt(Seconds));
		SecondsOutput.Append(":");
	}
	else {
		SecondsOutput = FString::FromInt(Seconds);
		SecondsOutput.Append(":");
	}

	if (Minutes < 10) {
		MinutesOutput = "0";
		MinutesOutput.Append(FString::FromInt(Minutes));
		MinutesOutput.Append(":");
	}
	else {
		MinutesOutput = FString::FromInt(Minutes);
		MinutesOutput.Append(":");
	}

	MilliSecondsText->SetText(FText::FromString(MilliSecondsOutput));
	SecondsText->SetText(FText::FromString(SecondsOutput));
	MinutesText->SetText(FText::FromString(MinutesOutput));
}
