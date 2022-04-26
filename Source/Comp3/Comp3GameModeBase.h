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
	
	int TotalCheckPoints = 0;
	int CheckPointsReached = 0;

	int TotalLaps = 3;
	int LapsCleared = 0;

	void SetTotalCheckPoints(int Increase);

	void LapCleared();
};
