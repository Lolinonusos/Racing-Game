// Fill out your copyright notice in the Description page of Project Settings.


#include "RacingGameInstance.h"
#include "../UI/GameHUD.h"

void URacingGameInstance::Init() {
	Super::Init();
}

void URacingGameInstance::Shutdown() {
	Super::Shutdown();
}

void URacingGameInstance::StartGameInstance() {
	Super::StartGameInstance();
}

void URacingGameInstance::SetGameAudio(float NewValue) {
	GameVolume = NewValue;
	UE_LOG(LogTemp, Warning, TEXT("Audio: %f"), GameVolume);
}

float URacingGameInstance::GetGameAudio() {
	return GameVolume;
}

