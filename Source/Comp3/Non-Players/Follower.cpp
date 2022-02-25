// Fill out your copyright notice in the Description page of Project Settings.


#include "Follower.h"


// Sets default values
AFollower::AFollower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FollowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FollowerMesh"));
	SetRootComponent(FollowerMesh);
	FollowerMaterial = CreateDefaultSubobject<UMaterial>(TEXT("FollowerMaterial"));
}

// Called when the game starts or when spawned
void AFollower::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFollower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFollower::ImHit()
{
	UE_LOG(LogTemp, Warning, TEXT("Follower got hit"));
	IsHit = true;
}