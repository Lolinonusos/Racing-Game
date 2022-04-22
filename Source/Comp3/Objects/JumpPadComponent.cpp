// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpPadComponent.h"

#include "Comp3/Vehicle/Car.h"

// Sets default values for this component's properties
UJumpPadComponent::UJumpPadComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UJumpPadComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UJumpPadComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UJumpPadComponent::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

