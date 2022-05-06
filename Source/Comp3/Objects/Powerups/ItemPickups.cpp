// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPickups.h"

AItemPickups::AItemPickups() {
	FWeapon Shotgun;
	Shotgun.WeaponName = "Shotgun";
	Shotgun.WeaponUses = 2;



	UniqueItems.Add(Shotgun);
}

void AItemPickups::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();

	NewLocation.Z = NewLocation.Z + (0.25f) * FMath::Sin(B * RunningTime - C) + D;

	SetActorLocation(NewLocation);
	RunningTime += DeltaTime;
}
