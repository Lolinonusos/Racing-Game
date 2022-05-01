// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Comp3GameModeBase.h"
#include "../Vehicle/Car.h"
#include "Kismet/GamePlayStatics.h"
#include "FixedPlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class COMP3_API UFixedPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	AComp3GameModeBase* FixedHUDPtr = Cast<AComp3GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	ACar* FixedCarPtr = Cast<ACar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	class UTextBlock* Laps;
	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	class UTextBlock* Checkpoints;
	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	class UTextBlock* AmmoText;
	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	class UTextBlock* SpecialText;
};
