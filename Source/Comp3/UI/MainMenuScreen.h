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
		class UButton* StarGameButton;
	UPROPERTY(BlueprintReadWrite, Category = "MainMenu", meta = (BindWidget))
		class UButton* OptionsButton;
	UPROPERTY(BlueprintReadWrite, Category = "MainMenu", meta = (BindWidget))
		class UButton* ExitButton;

	UFUNCTION()
	void ClickStartGame();
	UFUNCTION()
	void ClickOptions();
	UFUNCTION()
	void ClickExit();
};
