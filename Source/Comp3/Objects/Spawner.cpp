// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"

#include "Comp3/Non-Players/Follower.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnPoint = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnPoint"));
	SetRootComponent(SpawnPoint);

	PlayerSenseSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PlayerSenseSphere"));
	PlayerSenseSphere->SetupAttachment(GetRootComponent());
	PlayerSenseSphere->InitSphereRadius(15000.f);
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

void ASpawner::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bPlayerIsNearby = true;
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawner::SpawnActor, 1.f, true, 5.f);
}

void ASpawner::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	bPlayerIsNearby = false;
}

