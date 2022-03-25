// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHUD.h"
#include "Components/ProgressBar.h"
#include "Components/WidgetComponent.h"
void UEnemyHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);


	//FollowerPtr = Cast<AFollower>(->GetOwner());
	
	if (FollowerPtr) {
		UE_LOG(LogTemp, Warning, TEXT("ENTERED IF STATEMENT"));
		float HealthNow = FollowerPtr->ReturnCurrentHealth();
		float MaxHealthNow = FollowerPtr->ReturnMaxHealth();
		float HealthPercentage = (HealthNow / MaxHealthNow);

		EnemyHealthBar->SetPercent(HealthPercentage);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("SADGE"))
	}
	
	
}
