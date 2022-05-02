// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuScreen.generated.h"

/**
 * 
 */
UCLASS()
class COMP3_API UMainMenuScreen : public UUserWidget
{
	GENERATED_BODY()
		
public:
	virtual bool Initialize();
	

	UPROPERTY(BlueprintReadWrite, Category = "MainMenu", meta = (BindWidget))
		class UButton* MainMenuStartGameButton;
	UPROPERTY(BlueprintReadWrite, Category = "MainMenu", meta = (BindWidget))
		class UButton* MainMenuOptionsButton;
	UPROPERTY(BlueprintReadWrite, Category = "MainMenu", meta = (BindWidget))
		class UButton* MainMenuExitButton;

	UFUNCTION()
	void ClickStartGame();
	UFUNCTION()
	void ClickOptions();
	UFUNCTION()
	void ClickExit();
};
