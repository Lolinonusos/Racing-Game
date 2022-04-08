// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class COMP3_API ULevelSelectWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadWrite, Category = "LevelSelectUI", meta = (BindWidget))
	class UTextBlock* LevelName;

	UPROPERTY(BlueprintReadWrite, Category = "LevelSelectUI", meta = (BindWidget))
	class UButton* MoveLeft;
	UPROPERTY(BlueprintReadWrite, Category = "LevelSelectUI", meta = (BindWidget))
	class UButton* MoveRight;

	UPROPERTY(BlueprintReadWrite, Category = "LevelSelectUI", meta = (BindWidget))
	class UButton* SelectStage;
};
