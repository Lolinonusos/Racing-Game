// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Comp3GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class COMP3_API AComp3GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AComp3GameModeBase();
	virtual void BeginPlay() override;

	// Used in Shooter
	int TotalCheckPoints = 0;
	int CheckPointsReached = 0;

	int EnemiesAlive = 0;
	
	// Used in Time Trial
	int CheckpointScoreMultiplier = 0;
	
	int TotalLaps = 0;
	int LapsCleared = 0;

	void SetTotalCheckPoints(int Increase);

	bool LapCleared();
};
