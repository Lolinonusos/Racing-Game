// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Vehicle/Car.h"
#include "Kismet/GamePlayStatics.h"
#include "OptionsMenu.generated.h"

/**
 * 
 */
UCLASS()
class COMP3_API UOptionsMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	//ACar* PlayerPtr = Cast<ACar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	UPROPERTY(BlueprintReadWrite, Category = "Options Menu", meta = (BindWidget))
	class UTextBlock* AudioPercentText;
	UPROPERTY(BlueprintReadWrite, Category = "Options Menu", meta = (BindWidget))
	class UButton* ReturnButton;
	UPROPERTY(BlueprintReadWrite, Category = "Options Menu", meta = (BindWidget))
	class USlider* AudioSlider;
};
