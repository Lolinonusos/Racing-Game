// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KillBox.generated.h"

UCLASS()
class COMP3_API AKillBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKillBox();

	FVector CurrentCheckpointPosition;
	
	UPROPERTY()
	class UBoxComponent* KillArea = nullptr;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, 
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, 
		const FHitResult &SweepResult);
};
