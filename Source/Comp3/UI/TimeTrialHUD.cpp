// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeTrialHUD.h"
#include "Components/TextBlock.h"
#include "GameHUD.h"

// THIS DOCUMENT WAS WRITTEN BY JOACHIM

void UTimeTrialHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UTimeTrialHUD::DecreaseTime() {
	Score++;
	if (!bTimerIsFinished) {
		if (MilliSeconds - 1 >= 0) {
			MilliSeconds--;
		}
		else {
			if (Seconds == 0) {
				MilliSeconds = 0;
			}
			else {
				MilliSeconds = 99;
			}
			if (Seconds - 1 >= 0) {
				Seconds--;
			}
			else {
				if (Minutes - 1 >= 0) {
					Minutes--;
					Seconds = 60;
				}
				else {
					Minutes = 0;

				}
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
		if (Minutes <= 0 && Seconds <= 0 && MilliSeconds <= 0) {
			bTimerIsFinished = true;
		}
	}
	else {
		Score -= 4;
		Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD())->FinishTimeTrialMode();
	}
}

void UTimeTrialHUD::UpdateTimer() {
	MilliSecondsText->SetText(FText::FromString(MilliSecondsOutput));
	SecondsText->SetText(FText::FromString(SecondsOutput));
	MinutesText->SetText(FText::FromString(MinutesOutput));
}

void UTimeTrialHUD::AddTime(int Increase) {
	if (Seconds + Increase > 60) {
		Minutes++;
		Seconds += Increase - 60;
	}
	else {
		Seconds += Increase;
	}
}

void UTimeTrialHUD::IncreaseTimeScore() {
	SecondsSurvived++;
	FString SecondsScoreOutput = "Seconds Survived: ";
	SecondsScoreOutput.Append(FString::FromInt(SecondsSurvived));
	SecondsScore->SetText(FText::FromString(SecondsScoreOutput));
}
