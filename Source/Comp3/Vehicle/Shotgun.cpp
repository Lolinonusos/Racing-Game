// Fill out your copyright notice in the Description page of Project Settings.


#include "Shotgun.h"

AShotgun::AShotgun() {
	PrimaryActorTick.bCanEverTick = true;
	
}

void AShotgun::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorForwardVector() * TravelSpeed * DeltaTime;
	SetActorLocation(NewLocation);

	SecondsLived += DeltaTime;
	if (SecondsLived >= DeleteAfter) {
		this->Destroy();
	}
}
