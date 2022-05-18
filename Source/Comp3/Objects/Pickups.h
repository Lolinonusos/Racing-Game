// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Powerups.h"
#include "Pickups.generated.h"

// DOCUMENT WRITTEN BY JOACHIM

UCLASS()
class COMP3_API APickups : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickups();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickups")
		class UStaticMeshComponent* PickupStaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickups")
		FVector PickupPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickups")
		class APowerups* Item1 = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickups")
		class APowerups* Item2 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickups")
		class UBoxComponent* PickUpBoxCollision;

	UFUNCTION()
		void DeleteSelf();

	// Amplitude how fast
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PowerUp float")
		float A;

	// Period 2 * PI / ( ABS B )
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PowerUp float")
		float B = 1;

	// PHase Shift ( C / B )
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PowerUp float")
		float C;

	// Vertical Shift
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PowerUp float")
		float D;

	float RunningTime;

	UFUNCTION()
		void Levitate(float Time);

	UFUNCTION()
		void Respawn();

	UPROPERTY()
	float RespawnTime = 10.f;
	UPROPERTY()
	FTimerHandle RespawnTimerHandle;
	UPROPERTY()
	float TimeUntilRespawn{};

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, 
		UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, 
			const FHitResult &SweepResult);

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USoundBase* PickupSound;
};
