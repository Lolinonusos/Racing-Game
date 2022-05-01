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
		class UTextBlock* TimerText;

	

	void IncreaseTime();
	int MilliSeconds{};
	int Seconds{};
	int Minutes{};
};
