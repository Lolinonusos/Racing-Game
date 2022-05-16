// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPickups.h"

// DOCUMENT WRITTEN BY JOACHIM

AItemPickups::AItemPickups() {
	FWeapon Shotgun;
	Shotgun.WeaponName = "Shotgun";
	Shotgun.WeaponUses = 2;



	UniqueItems.Add(Shotgun);
}

void AItemPickups::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	Super::Levitate(DeltaTime);
}
