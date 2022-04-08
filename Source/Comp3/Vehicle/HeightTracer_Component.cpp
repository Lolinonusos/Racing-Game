// Fill out your copyright notice in the Description page of Project Settings.


#include "HeightTracer_Component.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "Math/UnrealMathUtility.h"

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

	RootComponenentVariable = Cast<UBoxComponent>(GetOwner()->GetRootComponent());
}

// Called every frame
void UHeightTracer_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// Value between 0 - 1
	float Alpha = (GetDistance() / MaxDistance);
	
	// Spring resistance like behaviour
	float Resistance = FMath::Lerp(HoverForce, 0.f, Alpha);

	// Do movement
	FVector Force = (Resistance * HitResult.ImpactNormal * RootComponenentVariable->GetMass());
	FRotator Rotation = RootComponenentVariable->GetComponentRotation();
	FVector Location = (RootComponenentVariable->GetCenterOfMass() + Rotation.RotateVector(GetRelativeLocation()));

	RootComponenentVariable->AddForceAtLocation(Force, Location);
}

float UHeightTracer_Component::GetDistance()
{
	FVector EndLocation = GetComponentLocation() + (GetUpVector() * - MaxDistance);
	FCollisionObjectQueryParams CollisionObjectQueryParams;
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	
	// Hit something
	if (GetOwner()->GetWorld()->LineTraceSingleByObjectType(HitResult, GetComponentLocation(), EndLocation, CollisionObjectQueryParams))
	{
		// Vector between the component and what it hit
		DrawDebugLine(GetOwner()->GetWorld(), GetComponentLocation(), EndLocation, FColor::Green, false, 1.f, 0, 5.f);
		return (HitResult.Location - GetComponentLocation()).Size();
	}
	DrawDebugLine(GetOwner()->GetWorld(), GetComponentLocation(), EndLocation, FColor::Red, false, 1.f, 0, 5.f);
	return 0.f;
	// return MaxDistance +1;
}