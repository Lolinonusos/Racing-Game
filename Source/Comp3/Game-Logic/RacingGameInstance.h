// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RacingGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class COMP3_API URacingGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	virtual void Shutdown() override;
	virtual void StartGameInstance() override;

	FString ChosenGameModeToPlay = "";
};
