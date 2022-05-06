// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Pickups.h"
#include "TimeTrialPickup.generated.h"

/**
 * 
 */
UCLASS()
class COMP3_API ATimeTrialPickup : public APickups
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	UPROPERTY()
	int TimeIncrease = 5;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, 
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, 
		const FHitResult &SweepResult);
};
