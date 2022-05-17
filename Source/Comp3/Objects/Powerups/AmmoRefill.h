// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Pickups.h"
#include "AmmoRefill.generated.h"

// DOCUMENT WRITTEN BY JOACHIM

UCLASS()
class COMP3_API AAmmoRefill : public APickups
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime) override;
	int AmmoRegen = 10;
	int GetAmmoRegen();

	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, 
		UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, 
			const FHitResult &SweepResult);
};
