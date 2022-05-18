// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Pickups.h"
#include "Components/WidgetComponent.h"
#include "TimeTrialPickup.generated.h"

/**
 * 
 */

// THIS DOCUMENT WAS WRITTEN BY JOACHIM

UCLASS()
class COMP3_API ATimeTrialPickup : public APickups
{
	GENERATED_BODY()

public:
	ATimeTrialPickup();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, 
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, 
		const FHitResult &SweepResult);
};
