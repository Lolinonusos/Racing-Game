// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Kismet/GamePlayStatics.h"

#include "Checkpoint.generated.h"

UCLASS()
class COMP3_API ACheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "CheckpointVariables")
	bool bIsGoal = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CheckpointBox")
	class UBoxComponent* CheckpointBox;

	UFUNCTION()
	void TurnOnCollision();

	FVector CurrentCheckpointPosition;
	
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	
};
