// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDClass.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Math/Color.h"
#include "../Game-Logic/RacingGameInstance.h"
#include "Kismet/GameplayStatics.h"

bool UHUDClass::Initialize() {
	Super::Initialize();

	URacingGameInstance* InstancePtr = Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	if (InstancePtr)
	{
		if (InstancePtr->ChosenGameModeToPlay != "Shooter")
		{
			HealthBar->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	
	return true;
}

void UHUDClass::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (PlayerShipPtr2) {
		// These function calls return the values needed to be shown on screen every tick
		float CurrentBoost = PlayerShipPtr2->GetBoost();
		float MaxBoost = PlayerShipPtr2->GetTotalBoost();

		float PlayersHealth = PlayerShipPtr2->GetCurrentHealth();
		float PlayersTotalhealth = PlayerShipPtr2->GetTotalHealth();

		float HealthPercentage = PlayersHealth / PlayersTotalhealth;

		float BoostBarPercent = CurrentBoost / MaxBoost;

		
		BoostBar->SetPercent(BoostBarPercent);
		if (HealthBar->Visibility != ESlateVisibility::Hidden)
		{
			HealthBar->SetPercent(HealthPercentage);
		}
	}
}
