// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "Components/WidgetComponent.h"
#include "PauseScreen.h"
#include "OptionsMenu.h"
#include "LevelSelectWidget.h"
#include "FocusedLevelSelectHUD.h"
#include "TimeTrialHUD.h"
#include "FixedPlayerHUD.h"

#include "Kismet/GameplayStatics.h"
#include "../Game-Logic/RacingGameInstance.h"

#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class COMP3_API AGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	AGameHUD();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> OptionsWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> LevelSelectWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> FocusedLevelSelectWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> TimeTrialHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> FixedPlayerHUDWidgetClass;

	UFUNCTION(BlueprintCallable)
		void UpdateSliderPercentage();

	UFUNCTION(BlueprintCallable)
		void OpenOptionsMenu();

	UFUNCTION(BlueprintCallable)
		void CloseOptionsMenu();

	UFUNCTION(BlueprintCallable)
		void OpenOptionsMenuFromMain();

	UFUNCTION(BlueprintCallable)
		void CloseOptionsMenuFromMain();

	UFUNCTION(BlueprintCallable)
		void OpenPauseMenu();

	UFUNCTION(BlueprintCallable)
		void ClosePauseMenu();

	UFUNCTION(BlueprintCallable)
		void FocusOnPlanet();

	UFUNCTION(BlueprintCallable)
		void LeaveFocusOnPlanet();

	UFUNCTION(BlueprintCallable)
		FString GetGameModeSelected();

	UFUNCTION(BlueprintCallable)
		void SetupHUDForRacingMode();

	UFUNCTION(BlueprintCallable)
		void SetupHUDForTimeTrialMode();

private:
	UPauseScreen* PauseWidget;
	UOptionsMenu* OptionsWidget;
	ULevelSelectWidget* LevelSelectWidget;
	UFocusedLevelSelectHUD* FocusedLevelSelectWidget;
	UTimeTrialHUD* TimeTrialHUDWidget;
	UFixedPlayerHUD* FixedPlayerHUDWidget;
};
