// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups.h"

// Sets default values
APickups::APickups()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PickupStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupStaticMesh"));
	SetRootComponent(PickupStaticMesh);
	
}

// Called when the game starts or when spawned
void APickups::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickups::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

