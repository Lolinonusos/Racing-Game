// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoRefill.h"
#include "../../Vehicle/Car.h"

// DOCUMENT WRITTEN BY JOACHIM

void AAmmoRefill::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	Super::Levitate(DeltaTime);
}

int AAmmoRefill::GetAmmoRegen() {
	return AmmoRegen;
}

void AAmmoRefill::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
		Super::OnOverlap(OverlappedComponent, OtherActor, OtherComponent, OtherBodyIndex, bFromSweep, SweepResult);

	if (OtherActor->IsA(ACar::StaticClass()))
	{
		Cast<ACar>(OtherActor)->AmmoTotal += GetAmmoRegen();
		Super::DeleteSelf();
	}
}
