// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/UserWidget.h"
#include "../Non-Players/Follower.h"
#include "EnemyHUD.generated.h"

/**
 * 
 */
UCLASS()
class COMP3_API UEnemyHUD : public UUserWidget
{
	GENERATED_BODY()
public:

	//AFollower* FollowerPtr = nullptr;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	UPROPERTY(BlueprintReadWrite, Category = "Enemy UI", meta = (BindWidget))
		class UProgressBar* EnemyHealthBar;

	UPROPERTY(BlueprintReadWrite, Category = "Enemy UI")
		AFollower* FollowerPtr {};
};
