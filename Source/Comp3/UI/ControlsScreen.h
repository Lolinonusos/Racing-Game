// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ControlsScreen.generated.h"

/**
 * 
 */
UCLASS()
class COMP3_API UControlsScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize();

	UPROPERTY(BlueprintReadWrite, Category = "Main Menu", meta = (BindWidget))
		class UButton* ControlsReturnButton;
	
	UFUNCTION()
		void ClickedControlsReturnBtn();
};
