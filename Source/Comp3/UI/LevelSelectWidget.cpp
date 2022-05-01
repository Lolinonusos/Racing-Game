// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSelectWidget.h"
#include "Components/TextBlock.h"
#include "../GameHUD.h"
#include "Components/Button.h"

bool ULevelSelectWidget::Initialize() {
	Super::Initialize();

	MoveLeft->OnClicked.AddDynamic(this, &ULevelSelectWidget::WidMoveCameraLeft);
	MoveRight->OnClicked.AddDynamic(this, &ULevelSelectWidget::WidMoveCameraRight);
	SelectStage->OnClicked.AddDynamic(this, &ULevelSelectWidget::WidSelectLevel);

	return true;
}

void ULevelSelectWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

	LevelName->SetText(FText::FromString(LevelSelectPtr->Levels[LevelSelectPtr->RotationNumber].PlanetName));
}

void ULevelSelectWidget::WidMoveCameraLeft() {
	LevelSelectPtr->MoveCameraLeft();
}

void ULevelSelectWidget::WidMoveCameraRight() {
	LevelSelectPtr->MoveCameraRight();
}

void ULevelSelectWidget::WidSelectLevel() {
	if (LevelSelectPtr->Levels[LevelSelectPtr->RotationNumber].bCanFocus) {
		LevelSelectPtr->SelectLevel();
		Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD())->FocusOnPlanet();
	}
}
