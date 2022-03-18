// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoRefill.h"

void AAmmoRefill::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();

	NewLocation.Z = NewLocation.Z + (0.25f) * FMath::Sin(B * RunningTime - C) + D;

	SetActorLocation(NewLocation);
	RunningTime += DeltaTime;
}