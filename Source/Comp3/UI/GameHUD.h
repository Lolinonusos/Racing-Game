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
#include "FinishedRaceScreen.h"
#include "MainMenuScreen.h"
#include "ControlsScreen.h"

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

	FTimerHandle TimeTrialTimerHandle;

	URacingGameInstance* HUDInstancePtr = Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

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

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> FinishedRaceScreenWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> ControlsScreenWidgetClass;

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

	UFUNCTION()
		void SetupHUDForShooterMode();

	UFUNCTION()
		void SetupHUDForTimeTrialMode();

	UFUNCTION()
		void UpdateTimer();

	UFUNCTION()
		void ShowFinishScreen();

	UFUNCTION()
		void ShowMainMenu();

	UFUNCTION()
		void ShowControls();

	UFUNCTION()
		void HideControls();

	UFUNCTION()
		int GetTimeTrialScore();

	UFUNCTION()
		void FinishTimeTrialMode();

	UFUNCTION()
	 void IncreaseTime();

private:
	UPauseScreen* PauseWidget;
	UOptionsMenu* OptionsWidget;
	ULevelSelectWidget* LevelSelectWidget;
	UFocusedLevelSelectHUD* FocusedLevelSelectWidget;
	UTimeTrialHUD* TimeTrialHUDWidget;
	UFixedPlayerHUD* FixedPlayerHUDWidget;
	UFinishedRaceScreen* FinishedRaceScreenWidget;
	UMainMenuScreen* MainMenuWidget;
	UControlsScreen* ControlsScreenWidget;
};
