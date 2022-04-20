// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LevelSelect.generated.h"

UCLASS()
class COMP3_API ALevelSelect : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALevelSelect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION(BlueprintCallable)
	void MoveCamera(float AxisValue);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int RotationNumber = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Levels;

private:
	UPROPERTY(EditAnywhere, Category = "LevelSelectComponents")
	class UCameraComponent* LevelSelectCamera;

	UPROPERTY(EditAnywhere, Category = "LevelSelectComponents")
	class USpringArmComponent* LevelSelectSpringArm;

	UPROPERTY(EditAnywhere, Category = "sdsd")
		class UStaticMeshComponent* sdsd;
};
