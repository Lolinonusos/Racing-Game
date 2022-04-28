// Fill out your copyright notice in the Description page of Project Settings.


#include "KillBox.h"
#include "Components/BoxComponent.h"
#include "Comp3/Vehicle/Car.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AKillBox::AKillBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKillBox::BeginPlay()
{
	Super::BeginPlay();

	
	if (KillArea) {
		KillArea->OnComponentBeginOverlap.AddDynamic(this, &AKillBox::OnOverlap);
	}
}

// Called every frame
void AKillBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKillBox::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(ACar::StaticClass()))
	{
		ACar* CarPtr = Cast<ACar>(GetWorld()->SpawnActor(ACar::StaticClass()));
		
	}
}

