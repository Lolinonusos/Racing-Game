// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSelectWidget.h"
#include "Components/TextBlock.h"

void ULevelSelectWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

	LevelName->SetText(FText::FromString("Default Name"));
}