// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LevelSelectWidget.h"
#include "FocusedLevelSelectHUD.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class COMP3_API AGameHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UUserWidget> LevelSelectClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UUserWidget> FocusedLevelClass;
private:
	UPROPERTY()
	class ULevelSelectWidget* LevelSelect{nullptr};
	UPROPERTY()
	class UFocusedLevelSelectHUD* FocusedLevel{nullptr};
};
