// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Vehicle/Car.h"
#include "Non-Players/Follower.h"
#include "Countdown.generated.h"

class UTextRenderComponent;

UCLASS()
class COMP3_API ACountdown : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACountdown();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int TimerTime;
	UTextRenderComponent* CountdownText{ nullptr };

	FTimerHandle CountdownTimerHandle;

	UPROPERTY(EditAnywhere)
	USoundBase* CountdownSound{ nullptr };

	void AdvanceTimer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Countdown")
		TArray<UStaticMeshComponent*> CountdownBalls;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Countdown")
		TSubclassOf<AActor> FollowerActor;

	
};
