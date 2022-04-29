// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "Components/WidgetComponent.h"
#include "UI/PauseScreen.h"
#include "UI/OptionsMenu.h"

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

private:
	UPauseScreen* PauseWidget;
	UOptionsMenu* OptionsWidget;
};
