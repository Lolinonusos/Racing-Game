// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Pickups.h"
#include "AmmoRefill.generated.h"


UCLASS()
class COMP3_API AAmmoRefill : public APickups
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime) override;
};
