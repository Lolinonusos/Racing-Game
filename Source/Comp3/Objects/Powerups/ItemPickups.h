// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Pickups.h"
#include "ItemPickups.generated.h"

/**
 * 
 */
UCLASS()
class COMP3_API AItemPickups : public APickups
{
	GENERATED_BODY()
		
public:
	AItemPickups();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickups")
		TArray<FString> UniqueItems;
	
	virtual void Tick(float DeltaTime) override;
};
