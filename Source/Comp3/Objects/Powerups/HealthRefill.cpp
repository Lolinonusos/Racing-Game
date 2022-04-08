// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthRefill.h"


void AHealthRefill::Tick(float DeltaTime) {
	FVector NewLocation = GetActorLocation();

	NewLocation.Z = NewLocation.Z + (0.25f) * FMath::Sin(B * RunningTime - C) + D;

	SetActorLocation(NewLocation);
	RunningTime += DeltaTime;
}

float AHealthRefill::GetHealthRegen() {
	return HealthRegen;
}
