// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FinishedRaceScreen.generated.h"

/**
 * 
 */
UCLASS()
class COMP3_API UFinishedRaceScreen : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize();

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (BindWidget))
		class UTextBlock* FinishedText;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (BindWidget))
		class UButton* RestartButton;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (BindWidget))
		class UButton* MainMenuButton;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (BindWidget))
		class UTextBlock* TimeTrialText;

	UFUNCTION()
		void FinishClickRestartBtn();

	UFUNCTION()
		void FinishClickMainMenuBtn();

	UFUNCTION()
		void CalculateTimeTrialScore();
};
