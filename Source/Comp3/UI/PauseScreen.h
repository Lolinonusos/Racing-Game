// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseScreen.generated.h"

/**
 * 
 */
class URacingGameInstance;

UCLASS()
class COMP3_API UPauseScreen : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize();

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadWrite, Category = "Pause Screen", meta = (BindWidget))
		class UTextBlock* PauseScreenText;
	UPROPERTY(BlueprintReadWrite, Category = "Pause Screen", meta = (BindWidget))
		class UButton* ResumeButton;
	UPROPERTY(BlueprintReadWrite, Category = "Pause Screen", meta = (BindWidget))
		class UButton* OptionsButton;
	UPROPERTY(BlueprintReadWrite, Category = "Pause Screen", meta = (BindWidget))
		class UButton* RestartButton;
	UPROPERTY(BlueprintReadWrite, Category = "Pause Screen", meta = (BindWidget))
		class UButton* MenuButton;
	UPROPERTY(BlueprintReadWrite, Category = "Pause Screen", meta = (BindWidget))
		class UButton* PauseMenuControlsButton;

	UPROPERTY(EditDefaultsOnly, Category = "Pause Screen")
		USoundBase* ClickingSound;

	UPROPERTY()
	URacingGameInstance* PauseMenuInstancePtr;

	UFUNCTION()
		void ClickResumeBtn();
	UFUNCTION()
		void ClickOptionsBtn();
	UFUNCTION()
		void ClickRestartBtn();
	UFUNCTION()
		void ClickMenuBtn();
	UFUNCTION()
		void ClickControlsBtn();
};
