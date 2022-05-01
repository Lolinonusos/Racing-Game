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
	FString ChosenGameModeToPlay = "";
};
