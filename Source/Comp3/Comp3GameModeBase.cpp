// Copyright Epic Games, Inc. All Rights Reserved.


#include "Comp3GameModeBase.h"
#include "GameHUD.h"
#include "Kismet/GameplayStatics.h"

void AComp3GameModeBase::BeginPlay() {
	Super::BeginPlay();

	//AGameHUD* GMBGameHUDPtr = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	//if (GMBGameHUDPtr->GetGameModeSelected() == "Racing") {
	//	// Player selecteed racing mode
	//	GMBGameHUDPtr->OpenOptionsMenu();
	//}
	//else if (GMBGameHUDPtr->GetGameModeSelected() == "Time") {
	//	// Player selected time trial mode
	//	GMBGameHUDPtr->CloseOptionsMenu();
	//}
}

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
