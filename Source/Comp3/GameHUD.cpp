// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "LevelSelectWidget.h"
#include "FocusedLevelSelectHUD.h"

void AGameHUD::BeginPlay() {
	Super::BeginPlay();

	//LevelSelect = CreateWidget<ULevelSelectWidget>(GetWorld(), LevelSelectClass);
	//LevelSelect->AddToViewport();
}