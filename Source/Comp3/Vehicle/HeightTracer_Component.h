// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "HeightTracer_Component.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMP3_API UHeightTracer_Component : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHeightTracer_Component();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	class UBoxComponent* RootComponentVariable;
	
	float HoverForce = 2000.f;
	
	float MaxDistance = 200.f;

	bool bInAir;
	float AirTime;
	
	FHitResult HitResult;
	float GetDistance();


};
