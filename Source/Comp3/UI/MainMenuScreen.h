// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MainMenuScreen.generated.h"


/**
 * 
 */
class AGameHUD;
class URacingGameInstance;
UCLASS()
class COMP3_API UMainMenuScreen : public UUserWidget
{
	GENERATED_BODY()
		
public:
	virtual bool Initialize();
	

	UPROPERTY(BlueprintReadWrite, Category = "Main Menu", meta = (BindWidget))
		class UButton* MainMenuStartGameButton;
	UPROPERTY(BlueprintReadWrite, Category = "Main Menu", meta = (BindWidget))
		class UButton* MainMenuOptionsButton;
	UPROPERTY(BlueprintReadWrite, Category = "Main Menu", meta = (BindWidget))
		class UButton* MainMenuExitButton;
	UPROPERTY(BlueprintReadWrite, Category = "Main Menu", meta = (BindWidget))
		class UButton* MainMenuControlsButton;

	UPROPERTY(EditDefaultsOnly, Category = "Main Menu")
		USoundBase* MainMenuClickSound;

	UPROPERTY()
	AGameHUD* MainMenuHUDPtr;
	UPROPERTY()
	URacingGameInstance* MainMenuInstancePtr;

	UFUNCTION()
	void ClickStartGame();
	UFUNCTION()
	void ClickOptions();
	UFUNCTION()
	void ClickExit();
	UFUNCTION()
	void ClickControlsButton();
};
