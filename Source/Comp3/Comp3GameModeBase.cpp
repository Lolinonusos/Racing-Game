// Copyright Epic Games, Inc. All Rights Reserved.


#include "Comp3GameModeBase.h"

AComp3GameModeBase::AComp3GameModeBase() {
	TotalCheckPoints = 0;
}

void AComp3GameModeBase::SetTotalCheckPoints(int Increase) {
	TotalCheckPoints += Increase;
}

bool AComp3GameModeBase::LapCleared()
{
	if (CheckPointsReached >= TotalCheckPoints)
	{
		LapsCleared += 1;
		CheckPointsReached = 0;
		
		if (LapsCleared >= TotalLaps)
		{
			// Win, but only in shooter mode
		}
		return true;
	}
	return false;
}
