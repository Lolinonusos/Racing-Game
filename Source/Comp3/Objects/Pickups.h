// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Powerups.h"
#include "Pickups.generated.h"


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
};
