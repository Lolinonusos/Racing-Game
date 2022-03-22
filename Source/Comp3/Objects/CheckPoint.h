// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckPoint.generated.h"

UCLASS()
class COMP3_API ACheckPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CheckpointVariables")
	int CheckpointsReached;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CheckpointVariables")
	int TotalCheckPoints;

	UPROPERTY(EditAnywhere, Category = "CheckpointVariables")
	bool bIsGoal;
};