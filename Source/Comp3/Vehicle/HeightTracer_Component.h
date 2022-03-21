// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
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
	
	float GetDistance(float MaxDistance = 1000);

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Springs")
	float Resistance;
};
