// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LevelSelect.generated.h"

USTRUCT(BlueprintType)
struct FPlanet {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString PlanetName;

	FRotator IdealCameraRotation;
	FVector IdealCameraLocation;

	FVector FocusedCameraLocation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bCanFocus;
};

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
	void MoveCameraLeft();
	UFUNCTION(BlueprintCallable)
	void MoveCameraRight();
	UFUNCTION(BlueprintCallable)
	void SelectLevel();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int RotationNumber = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPlanet> Levels;

	bool bStartingToLerp = false;
	bool bMovingRight = false;
	bool bPausedControls = false;

	UPROPERTY(BlueprintReadOnly)
	bool bIsEnteringFocus = false;
	
	UPROPERTY(BlueprintReadWrite)
	bool bIsLeavingFocus = false;
	
	float Alpha = 0.f;
	float CameraChangeSpeed = 0.01f;
	float FocusAlpha = 0.f;
private:
	UPROPERTY(EditAnywhere, Category = "LevelSelectComponents")
	class UCameraComponent* LevelSelectCamera;

	UPROPERTY(EditAnywhere, Category = "LevelSelectComponents")
	class USpringArmComponent* LevelSelectSpringArm;

	UPROPERTY(EditAnywhere, Category = "sdsd")
		class UStaticMeshComponent* sdsd;
};
