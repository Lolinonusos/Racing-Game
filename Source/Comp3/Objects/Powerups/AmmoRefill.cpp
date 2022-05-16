// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoRefill.h"

// DOCUMENT WRITTEN BY JOACHIM

void AAmmoRefill::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	Super::Levitate(DeltaTime);
}

int AAmmoRefill::GetAmmoRegen() {
	return AmmoRegen;
}
