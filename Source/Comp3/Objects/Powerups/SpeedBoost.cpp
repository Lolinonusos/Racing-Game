// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedBoost.h"

ASpeedBoost::ASpeedBoost() {

}

void ASpeedBoost::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
		
	NewLocation.Z = NewLocation.Z + (0.5f) * FMath::Sin(B * RunningTime - C) + D; 

	SetActorLocation(NewLocation);
	RunningTime += DeltaTime;
	
}