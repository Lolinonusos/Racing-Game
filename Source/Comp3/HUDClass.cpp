// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDClass.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Math/Color.h"

void UHUDClass::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (PlayerShipPtr2) {
		int Ammo = PlayerShipPtr2->GetAmmo();
		float CurrentBoost = PlayerShipPtr2->GetBoost();
		float MaxBoost = PlayerShipPtr2->GetTotalBoost();
		FString CurrentSpecial = "Special: ";
		CurrentSpecial.Append(PlayerShipPtr2->GetSpecial());
		
		FString CurrentAmmo = "Ammo: ";
		CurrentAmmo.Append(FString::FromInt(Ammo));

		float BoostBarPercent = CurrentBoost / MaxBoost;

		BoostBar->SetPercent(BoostBarPercent);
		AmmoNum->SetText(FText::FromString(CurrentAmmo));
		
		if (PlayerShipPtr2->GetSpecial() == "") {
			Special->SetText(FText::FromString(CurrentSpecial.Append("None")));
		}
		else {
			Special->SetText(FText::FromString(CurrentSpecial));
			
		}
	}
	else { return; }
}
