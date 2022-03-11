// Fill out your copyright notice in the Description page of Project Settings.


#include "Powerups.h"

// Sets default values
APowerups::APowerups()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PowerupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PowerupMesh"));
	SetRootComponent(PowerupMesh);
	
}

// Called when the game starts or when spawned
void APowerups::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerups::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

