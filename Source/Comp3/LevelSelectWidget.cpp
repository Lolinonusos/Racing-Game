// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSelectWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void ULevelSelectWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("Level Name in Widget: %s"), *LevelSelectPtr->Levels[LevelSelectPtr->RotationNumber].PlanetName);
	LevelName->SetText(FText::FromString(LevelSelectPtr->Levels[LevelSelectPtr->RotationNumber].PlanetName));
	//UE_LOG(LogTemp, Warning, TEXT("Level Name in Widget: %s"), *LevelSelectPtr->Levels[LevelSelectPtr->RotationNumber].PlanetName);
}