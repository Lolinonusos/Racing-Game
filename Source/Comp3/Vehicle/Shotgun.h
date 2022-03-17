// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "Shotgun.generated.h"


UCLASS()
class COMP3_API AShotgun : public ABullet
{
	GENERATED_BODY()

public:
	AShotgun();

	virtual void Tick(float DeltaTime) override;
};
