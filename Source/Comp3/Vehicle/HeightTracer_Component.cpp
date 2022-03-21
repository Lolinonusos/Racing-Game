// Fill out your copyright notice in the Description page of Project Settings.


#include "HeightTracer_Component.h"


// Sets default values for this component's properties
UHeightTracer_Component::UHeightTracer_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}

// Called when the game starts
void UHeightTracer_Component::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

// Called every frame
void UHeightTracer_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UHeightTracer_Component::GetDistance(float MaxDistance)
{
	FHitResult HitResult;
	FVector EndLocation = GetComponentLocation() + (GetUpVector() * -MaxDistance);
	FCollisionObjectQueryParams CollisionObjectQueryParams;
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);

	// Hit something
	if (GetOwner()->GetWorld()->LineTraceSingleByObjectType(HitResult, GetComponentLocation(), EndLocation, CollisionObjectQueryParams))
	{
		// Vector between the component and what it hit
		return (HitResult.Location - GetComponentLocation()).Size();
	}
	return MaxDistance +1;
}