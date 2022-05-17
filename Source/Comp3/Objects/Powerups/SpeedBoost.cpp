// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedBoost.h"
#include "../../Vehicle/Car.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnitConversion.h"

ASpeedBoost::ASpeedBoost() {

}

int ASpeedBoost::ReturnBoost() {
	return BoostRegen;
}

void ASpeedBoost::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	Super::OnOverlap(OverlappedComponent, OtherActor, OtherComponent, OtherBodyIndex, bFromSweep, SweepResult);

	if (OtherActor->IsA(ACar::StaticClass()))
	{
		//UE_LOG(LogTemp, Warning, TEXT("COLLIDED WITH SPEED BOOST"))
		ACar* SpeedCarPtr = Cast<ACar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		SpeedCarPtr->BoostAmount = ReturnBoost();
		if (SpeedCarPtr->BoostAmount + ReturnBoost() > SpeedCarPtr->MaxBoostAmount)
		{
			SpeedCarPtr->BoostAmount = SpeedCarPtr->MaxBoostAmount;
		} else
		{
			SpeedCarPtr->BoostAmount += ReturnBoost();
		}
		Super::DeleteSelf();
	}
}

void ASpeedBoost::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	Super::Levitate(DeltaTime);
	
}
