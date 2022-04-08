// Copyright Epic Games, Inc. All Rights Reserved.


#include "Comp3GameModeBase.h"

AComp3GameModeBase::AComp3GameModeBase() {
	TotalCheckPoints = 0;
}

void AComp3GameModeBase::SetTotalCheckPoints(int Increase) {
	TotalCheckPoints += Increase;
}
