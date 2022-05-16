// Copyright Epic Games, Inc. All Rights Reserved.


#include "Comp3GameModeBase.h"
#include "UI/GameHUD.h"
#include "Kismet/GameplayStatics.h"

void AComp3GameModeBase::BeginPlay() {
	Super::BeginPlay();

	URacingGameInstance* GMBInstancePtr = Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GMBInstancePtr) {
		if (GMBInstancePtr->ChosenGameModeToPlay == "Racing") {
			TotalLaps = 3;
			UE_LOG(LogTemp, Warning, TEXT("ENTERED RACNIG MODE"))
		}
		else if (GMBInstancePtr->ChosenGameModeToPlay == "Time") {
			TotalLaps = 99;
			UE_LOG(LogTemp, Warning, TEXT("ENTERED TIME TRIAL MODE"))
		}
		UE_LOG(LogTemp, Warning, TEXT("Audio: %f"), GMBInstancePtr->GetGameAudio());
	}
}

AComp3GameModeBase::AComp3GameModeBase() {
	TotalCheckPoints = 0;
}

void AComp3GameModeBase::SetTotalCheckPoints(int Increase) {
	TotalCheckPoints += Increase;
	
}

// If true counts a lap and resets checkpoint collision
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
