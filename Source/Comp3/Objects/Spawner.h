// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class COMP3_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SpawnActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	class USphereComponent* PlayerSenseSphere;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	class UBoxComponent* SpawnPoint;

	bool bPlayerIsNearby = false;
	FTimerHandle SpawnTimer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> SpawnAI;
	
	UFUNCTION()
void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
				UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);
};
