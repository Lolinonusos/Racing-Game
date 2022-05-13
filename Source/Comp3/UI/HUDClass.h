// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Vehicle/Car.h"
#include "../Comp3GameModeBase.h"
#include "Kismet/GamePlayStatics.h"
#include "HUDClass.generated.h"

/**
 * 
 */
UCLASS()
class COMP3_API UHUDClass : public UUserWidget
{
	GENERATED_BODY()
	
public:

	ACar* PlayerShipPtr2 = Cast<ACar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	AComp3GameModeBase* GameModePtr2 = Cast<AComp3GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	virtual bool Initialize() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (BindWidget))
		class UProgressBar* BoostBar;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (BindWidget))
		class UProgressBar* HealthBar;
};
