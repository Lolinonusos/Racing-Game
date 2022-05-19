// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "OffRoadHover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMP3_API UOffRoadHover : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOffRoadHover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Get ACar's rootcomponent
	UPROPERTY()
	class UBoxComponent* RootComponentVariable;
	
	float HoverForce = 1000.f;
	
	float MaxDistance = 150.f;

	bool bInAir;
	float AirTime;
	
	FHitResult HitResult;
	FCollisionObjectQueryParams CollisionObjectQueryParams;
	
	float GetDistance();
};
