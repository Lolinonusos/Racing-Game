// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups.h"
#include "Components/BoxComponent.h"
#include "../Vehicle/Car.h"


// DOCUMENT WRITTEN BY JOACHIM

// Sets default values
APickups::APickups()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PickupStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupStaticMesh"));
	SetRootComponent(PickupStaticMesh);

	PickUpBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PickUpBoxCollision"));
	PickUpBoxCollision->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void APickups::BeginPlay()
{
	Super::BeginPlay();

	if (PickUpBoxCollision) {
		PickUpBoxCollision->OnComponentBeginOverlap.AddDynamic(this, &APickups::OnOverlap);
	}
}

// Called every frame
void APickups::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Function written by Joachim
void APickups::DeleteSelf() {
	UE_LOG(LogTemp, Warning, TEXT("HIT BOX - THIS IS FROM PICKUPS"));
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &APickups::Respawn, 1.f, true, 0.f);
}


// Function written by Linus
void APickups::Levitate(float Time) {
	FVector NewLocation = GetActorLocation();

	NewLocation.Z = NewLocation.Z + (0.25f) * FMath::Sin(B * RunningTime - C) + D;

	SetActorLocation(NewLocation);
	RunningTime += Time;
}

// Function written by Joachim
void APickups::Respawn() {
	TimeUntilRespawn += 1.f;
	if (TimeUntilRespawn >= RespawnTime) {
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);
		TimeUntilRespawn = 0;
		SetActorHiddenInGame(false);
		SetActorEnableCollision(true);
	}
}

void APickups::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	
}

