// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Pickups.h"
#include "ItemPickups.generated.h"

/**
 * 
 */

USTRUCT()
struct FWeapon {
	GENERATED_BODY()
public:
	FString WeaponName;
	int WeaponUses;
};

UCLASS()
class COMP3_API AItemPickups : public APickups
{
	GENERATED_BODY()
		
public:
	AItemPickups();
	UPROPERTY(EditAnywhere, Category = "Pickups")
		TArray<FWeapon> UniqueItems;
	
	virtual void Tick(float DeltaTime) override;
};
