// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimeTrialHUD.generated.h"

/**
 * 
 */
// THIS DOCUMENT WAS WRITTEN BY JOACHIM

UCLASS()
class COMP3_API UTimeTrialHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadWrite, Category = "UI | TimeTrial", meta = (BindWidget))
		class UTextBlock* MinutesText;
	UPROPERTY(BlueprintReadWrite, Category = "UI | TimeTrial", meta = (BindWidget))
		class UTextBlock* SecondsText;
	UPROPERTY(BlueprintReadWrite, Category = "UI | TimeTrial", meta = (BindWidget))
		class UTextBlock* MilliSecondsText;
	UPROPERTY(BlueprintReadWrite, Category = "UI | TimeTrial", meta = (BindWidget))
	class UTextBlock* SecondsScore;

	void DecreaseTime();
	void UpdateTimer();
	void AddTime(int Increase);
	void IncreaseTimeScore();
	int MilliSeconds{};
	int Seconds{};
	int Minutes = 1;
	bool bTimerIsFinished = false;
	int Score{};
	int PickupsCollected{};
	int CheckpointsReached{0};
	int SecondsSurvived{0};

	FString MinutesOutput = "";
	FString SecondsOutput;
	FString MilliSecondsOutput;

	// Progressbaren er full når spilleren har mer enn 1 minutt igjen
	UPROPERTY()
	class UProgressBar* TimerBar;

	UPROPERTY()
	class UTextBlock* TimerMinutes;
	
	UPROPERTY()
	class UTextBlock* TimerSeconds;

	UPROPERTY()
	class UTextBlock* TimerMilliSeconds;

};
