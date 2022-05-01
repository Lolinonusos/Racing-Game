// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimeTrialHUD.generated.h"

/**
 * 
 */
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

	

	void IncreaseTime();
	int MilliSeconds{};
	int Seconds{};
	int Minutes{};

	FString MinutesOutput = "";
	FString SecondsOutput;
	FString MilliSecondsOutput;
};
