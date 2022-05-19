// Fill out your copyright notice in the Description page of Project Settings.


#include "OffRoadHover.h"
//#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UOffRoadHover::UOffRoadHover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOffRoadHover::BeginPlay()
{
	Super::BeginPlay();

	RootComponentVariable = Cast<UBoxComponent>(GetOwner()->GetRootComponent());

	
}


// Called every frame
void UOffRoadHover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Value between 0 - 1
	float Alpha = (GetDistance() / MaxDistance);
	
	// Spring resistance like behaviour
	float Resistance = FMath::Lerp(HoverForce, 0.f, Alpha);

	// Do movement
	FVector Force = (Resistance * HitResult.ImpactNormal * RootComponentVariable->GetMass());
	FRotator Rotation = RootComponentVariable->GetComponentRotation();
	FVector Location = (RootComponentVariable->GetCenterOfMass() + Rotation.RotateVector(GetRelativeLocation()));

	RootComponentVariable->AddForceAtLocation(Force, Location);
}

float UOffRoadHover::GetDistance()
{
	FVector EndLocation = GetComponentLocation() + (GetUpVector() * - MaxDistance);
	
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_EngineTraceChannel1);
	
	// Hit something
	if (GetOwner()->GetWorld()->LineTraceSingleByObjectType(HitResult, GetComponentLocation(), EndLocation, CollisionObjectQueryParams))
	{
		//DrawDebugLine(GetOwner()->GetWorld(), GetComponentLocation(), EndLocation, FColor::Green, false, 1.f, 0, 5.f);

		// Vector between the component and what it hit
		return (HitResult.Location - GetComponentLocation()).Size();
		//bInAir = false;
	}
	//DrawDebugLine(GetOwner()->GetWorld(), GetComponentLocation(), EndLocation, FColor::Red, false, 1.f, 0, 5.f);
	
	return 0.f;
}