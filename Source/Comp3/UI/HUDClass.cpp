// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDClass.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Math/Color.h"

void UHUDClass::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (PlayerShipPtr2) {
		// These function calls return the values needed to be shown on screen every tick
		int Ammo = PlayerShipPtr2->GetAmmo();
		float CurrentBoost = PlayerShipPtr2->GetBoost();
		float MaxBoost = PlayerShipPtr2->GetTotalBoost();
		FString CurrentSpecial = "Special: ";
		CurrentSpecial.Append(PlayerShipPtr2->GetSpecial());

		float PlayersHealth = PlayerShipPtr2->GetCurrentHealth();
		float PlayersTotalhealth = PlayerShipPtr2->GetTotalHealth();

		float HealthPercentage = PlayersHealth / PlayersTotalhealth;
		
		FString CurrentAmmo = "Ammo: ";
		CurrentAmmo.Append(FString::FromInt(Ammo));

		float BoostBarPercent = CurrentBoost / MaxBoost;

		
		BoostBar->SetPercent(BoostBarPercent);
		AmmoNum->SetText(FText::FromString(CurrentAmmo));
		HealthBar->SetPercent(HealthPercentage);
		
		// This if sentence checks if the special weapon slot for the player is empty
		if (PlayerShipPtr2->GetSpecial() == "") {
			// If it is, then change the text to "None"
			Special->SetText(FText::FromString(CurrentSpecial.Append("None")));
		}
		else {
			// If it is taken, check the weapon
			if (PlayerShipPtr2->GetSpecial() == "Shotgun") {
				
				// The shotgun has multiple uses, so check how many there are and change the text accordingly
				switch (PlayerShipPtr2->ShotgunUses) {
				case 2:
					Special->SetText(FText::FromString(CurrentSpecial.Append(" x2")));
					break;
				case 1:
					Special->SetText(FText::FromString(CurrentSpecial));
					break;
				default:
					Special->SetText(FText::FromString("None"));
					break;
				}
			}
			
			
		}
	}
	else { return; }
}
