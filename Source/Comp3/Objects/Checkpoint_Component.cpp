// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint_Component.h"
#include "Components/BoxComponent.h"

#include "../Comp3GameModeBase.h"

// Sets default values for this component's properties
UCheckpoint_Component::UCheckpoint_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CheckpointBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CheckpointBox"));
	
	// ...
}


// Called when the game starts
void UCheckpoint_Component::BeginPlay()
{
	Super::BeginPlay();

	// ...
	GameModePtr->TotalCheckPoints += 1;
}


// Called every frame
void UCheckpoint_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCheckpoint_Component::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

