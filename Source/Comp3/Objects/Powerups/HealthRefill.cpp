// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthRefill.h"

// DOCUMENT WRITTEN BY JOACHIM

void AHealthRefill::Tick(float DeltaTime) {
	FVector NewLocation = GetActorLocation();

	Super::Levitate(DeltaTime);
}

float AHealthRefill::GetHealthRegen() {
	return HealthRegen;
}
