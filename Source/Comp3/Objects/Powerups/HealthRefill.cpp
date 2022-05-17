// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthRefill.h"
#include "../../Vehicle/Car.h"
#include "Components/BoxComponent.h"

// DOCUMENT WRITTEN BY JOACHIM

void AHealthRefill::Tick(float DeltaTime) {
	FVector NewLocation = GetActorLocation();

	Super::Levitate(DeltaTime);
}

float AHealthRefill::GetHealthRegen() {
	return HealthRegen;
}


void AHealthRefill::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	if (OtherActor->IsA(ACar::StaticClass()))
	{
		GetHealthRegen();
		Super::DeleteSelf();
	}
}

