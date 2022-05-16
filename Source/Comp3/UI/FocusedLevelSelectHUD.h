// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../LevelSelect.h"
#include "Kismet/GamePlayStatics.h"
#include "FocusedLevelSelectHUD.generated.h"

/**
 * 
 */
class AGameHUD;
class URacingGameInstance;
UCLASS()
class COMP3_API UFocusedLevelSelectHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize();
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadWrite)
	ALevelSelect* FocusedLevelSelectPtr = Cast<ALevelSelect>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	UPROPERTY(BlueprintReadWrite)
	bool bGameModeSelected = false;
	UPROPERTY(BlueprintReadWrite)
	FString SelectedGameMode = "";
	// "Shooter" equals regular shooter mode
	// "Time" equals time trial mode

	UPROPERTY(BlueprintReadWrite, Category = "LevelSelectUI | Focused", meta = (BindWidget))
	class UTextBlock* FocusedLevelName;
	UPROPERTY(BlueprintReadWrite, Category = "LevelSelectUI | Focused", meta = (BindWidget))
	class UTextBlock* PlayButtonText;
	UPROPERTY(BlueprintReadWrite, Category = "LevelSelectUI | Focused", meta = (BindWidget))
	class UTextBlock* DescriptionNameText;
	UPROPERTY(BlueprintReadWrite, Category = "LevelSelectUI | Focused", meta = (BindWidget))
	class UTextBlock* DescriptionText;
	UPROPERTY(BlueprintReadWrite, Category = "LevelSelectUI | Focused", meta = (BindWidget))
	class UButton* ShooterModeButton;
	UPROPERTY(BlueprintReadWrite, Category = "LevelSelectUI | Focused", meta = (BindWidget))
	class UButton* TimeTrialModeButton;
	UPROPERTY(BlueprintReadWrite, Category = "LevelSelectUI | Focused", meta = (BindWidget))
	class UButton* PlayButton;
	UPROPERTY(BlueprintReadWrite, Category = "LevelSelectUI | Focused", meta = (BindWidget))
	class UButton* BackButton;
	UPROPERTY()
	AGameHUD* FocusedLevelSelectHUDPtr;
	UPROPERTY()
	URacingGameInstance* FocusedLevelSelectInstancePtr;
	UPROPERTY(EditDefaultsOnly)
	USoundBase* FocusedClickSelectSound;

	UFUNCTION()
		void ClickShooterModeBtn();
	UFUNCTION()
		void ClickTimeTrialModeBtn();
	UFUNCTION()
		void ClickBackButton();
	UFUNCTION()
		void ClickPlayButton();
	UFUNCTION()
		void ChangeGameModeDescription();
};
