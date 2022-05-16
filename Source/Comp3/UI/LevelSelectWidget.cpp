// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSelectWidget.h"
#include "Components/TextBlock.h"
#include "GameHUD.h"
#include "Components/Button.h"

bool ULevelSelectWidget::Initialize() {
	Super::Initialize();

	if (MoveLeft) {
		MoveLeft->OnClicked.AddDynamic(this, &ULevelSelectWidget::WidMoveCameraLeft);
	}
	if (MoveRight) {
		MoveRight->OnClicked.AddDynamic(this, &ULevelSelectWidget::WidMoveCameraRight);
	}
	if (SelectStage) {
		SelectStage->OnClicked.AddDynamic(this, &ULevelSelectWidget::WidSelectLevel);
	}
	if (!LevelSelectHUDPtr) {
		LevelSelectHUDPtr = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	}
	if (!LevelSelectInstancePtr) {
		LevelSelectInstancePtr = Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}
	

	return true;
}

void ULevelSelectWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

	LevelName->SetText(FText::FromString(LevelSelectPtr->Levels[LevelSelectPtr->RotationNumber].PlanetName));
}

void ULevelSelectWidget::WidMoveCameraLeft() {
	if (LevelSelectPtr->bPausedControls == false) {
		UGameplayStatics::PlaySound2D(GetWorld(), LevelSelectClickSound, LevelSelectInstancePtr->GetGameAudio(), 1.f, 0.f, nullptr, nullptr, true);
		LevelSelectPtr->MoveCameraLeft();
	}
}

void ULevelSelectWidget::WidMoveCameraRight() {
	UE_LOG(LogTemp, Warning, TEXT("The boolean value is %s"), (LevelSelectPtr->bPausedControls ? TEXT("true") : TEXT("false")));
	if (LevelSelectPtr->bPausedControls == false) {
		UGameplayStatics::PlaySound2D(GetWorld(), LevelSelectClickSound, LevelSelectInstancePtr->GetGameAudio(), 1.f, 0.f, nullptr, nullptr, true);
		LevelSelectPtr->MoveCameraRight();
	}
}

void ULevelSelectWidget::WidSelectLevel() {
	if (LevelSelectPtr->Levels[LevelSelectPtr->RotationNumber].bCanFocus) {
		if (!LevelSelectPtr->bIsLeavingFocus) {
			LevelSelectPtr->SelectLevel();
			LevelSelectHUDPtr->FocusOnPlanet();
			UGameplayStatics::PlaySound2D(GetWorld(), LevelSelectClickSound, LevelSelectInstancePtr->GetGameAudio(), 1.f, 0.f, nullptr, nullptr, true);
		}
	}
}
