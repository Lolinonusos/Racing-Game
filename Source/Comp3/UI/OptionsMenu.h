// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GamePlayStatics.h"
#include "OptionsMenu.generated.h"

/**
 * 
 */
UCLASS()
class COMP3_API UOptionsMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize();

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadWrite, Category = "Options Menu", meta = (BindWidget))
	class UTextBlock* AudioPercentText;
	UPROPERTY(BlueprintReadWrite, Category = "Options Menu", meta = (BindWidget))
	class UButton* ReturnButton;
	UPROPERTY(BlueprintReadWrite, Category = "Options Menu", meta = (BindWidget))
	class USlider* AudioSlider;

	UFUNCTION()
		void UpdateSliderPercentage();
	UFUNCTION()
		void ClickReturnBtn();

	UPROPERTY(EditDefaultsOnly, Category = "Options Menu")
		USoundBase* ReturnButtonSound;
};
