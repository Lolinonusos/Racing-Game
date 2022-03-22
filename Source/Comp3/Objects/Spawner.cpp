// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"

#include "Comp3/Non-Players/Follower.h"
#include "Components/BoxComponent.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnPoint = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnPoint"));
	SetRootComponent(SpawnPoint);
	
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawner::SpawnActor()
{
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();

	GetWorld()->SpawnActor<AFollower>(SpawnLocation, SpawnRotation);
}

