// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerBoostWidget.generated.h"

/**
 * 
 */
UCLASS()
class COMP3_API UTimerBoostWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	 int TimeIncrease = 3;
	
	 virtual bool Initialize();
	
	 UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	 class UTextBlock* TimeText;
};
