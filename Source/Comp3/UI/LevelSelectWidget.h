// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../LevelSelect.h"
#include "Kismet/GamePlayStatics.h"
#include "LevelSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class COMP3_API ULevelSelectWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual bool Initialize();

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ALevelSelect* LevelSelectPtr = Cast<ALevelSelect>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));


	UPROPERTY(BlueprintReadWrite, Category = "LevelSelectUI", meta = (BindWidget))
	class UTextBlock* LevelName;

	UPROPERTY(BlueprintReadWrite, Category = "LevelSelectUI", meta = (BindWidget))
	class UButton* MoveLeft;
	UPROPERTY(BlueprintReadWrite, Category = "LevelSelectUI", meta = (BindWidget))
	class UButton* MoveRight;

	UPROPERTY(BlueprintReadWrite, Category = "LevelSelectUI", meta = (BindWidget))
	class UButton* SelectStage;

	UFUNCTION()
	void WidMoveCameraLeft();
	UFUNCTION()
	void WidMoveCameraRight();
	UFUNCTION()
	void WidSelectLevel();
};
