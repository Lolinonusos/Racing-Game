// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "CountdownWidget.generated.h"

/**
 * 
 */
class URacingGameInstance;
UCLASS()
class COMP3_API UCountdownWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual bool Initialize();

	URacingGameInstance* CountdownInstancePtr;
	
	UPROPERTY(BlueprintReadWrite, Category = "HUD | Countdown", meta = (BindWidget))
	UImage* Light1;
	UPROPERTY(BlueprintReadWrite, Category = "HUD | Countdown", meta = (BindWidget))
	UImage* Light2;
	UPROPERTY(BlueprintReadWrite, Category = "HUD | Countdown", meta = (BindWidget))
	UImage* Light3;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* NextSecond;
	
	
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* YellowLight;
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* RedLight;
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* GreenLight;
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* BlackLight;

	UPROPERTY()
	int TimerSeconds = 0;
	
	UFUNCTION()
	void ChangeColorAndTime();
};
