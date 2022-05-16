// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Pickups.h"
#include "HealthRefill.generated.h"

/**
 * 
 */
// DOCUMENT WRITTEN BY JOACHIM

UCLASS()
class COMP3_API AHealthRefill : public APickups
{
	GENERATED_BODY()

	
public:
	virtual void Tick(float DeltaTime) override;
	float HealthRegen = 5;
	float GetHealthRegen();
};
