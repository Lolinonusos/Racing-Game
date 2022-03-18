// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Pickups.h"
#include "SpeedBoost.generated.h"

UCLASS()
class COMP3_API ASpeedBoost : public APickups
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

	ASpeedBoost();

	float InitialLocation;

	// Amplitude how fast
	UPROPERTY (EditAnywhere, BlueprintReadWrite, Category = "PowerUp float")
	float A;

	// Period 2 * PI / ( ABS B )
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PowerUp float")
	float B = 1;

	// PHase Shift ( C / B )
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PowerUp float")
	float C;

	// Vertical Shift
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PowerUp float")
	float D;

	float RunningTime;
};
