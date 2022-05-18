// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeTrialPickup.h"
#include "../../UI/GameHUD.h"
#include "../../Vehicle/Car.h"
#include "Components/BoxComponent.h"

// THIS DOCUMENT WAS WRITTEN BY JOACHIM

ATimeTrialPickup::ATimeTrialPickup() {

}

void ATimeTrialPickup::BeginPlay() {
	Super::BeginPlay();

	if (PickUpBoxCollision) {
		PickUpBoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ATimeTrialPickup::OnOverlap);
	}
	
}

void ATimeTrialPickup::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	Super::Levitate(DeltaTime);
}

void ATimeTrialPickup::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor->IsA(ACar::StaticClass())) {
		AGameHUD* PickupHUDPtr = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
		PickupHUDPtr->IncreaseTime("Pickups");
		PickupHUDPtr->IncreasePickupCount();
		
		Super::DeleteSelf();
	}
}
