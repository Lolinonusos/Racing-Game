// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Car.generated.h"

UCLASS()
class COMP3_API ACar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UFloatingPawnMovement* PawnMovementComponent = nullptr;

private:
	UPROPERTY(EditAnywhere, Category = "VehicleCamera")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "VehicleCamera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = "VehicleMesh")
	class UStaticMeshComponent* VehicleMesh;

	UPROPERTY(EditAnywhere, Category = "VehicleSounds")
	class USoundBase* DriveSound;
	
	UPROPERTY(EditAnywhere, Category = "VehicleSounds")
	class USoundBase* BrakeSound;

	UPROPERTY(EditAnywhere, Category = "VehicleSounds")
	class USoundBase* BoostSound;

	UPROPERTY(EditAnywhere, Category = "VehicleSound")
	class USoundBase* ShootingSound;

	UPROPERTY(EditAnywhere, Category = "VehicleSounds")
	class USoundBase* ReloadSound;

	UPROPERTY(EditAnywhere, Category = "VehicleVariables")
	float DriveSpeed = 1.f;

	UPROPERTY(EditAnywhere, Category = "VehicleVariables")
	float TurnSpeed = 1.f;

	void StartDriving();
	void StopDriving();
	bool bDriving = false;

	void StartBrake();
	void StopBrake();
	bool bBraking = false;

	void Turn(float AxisValue);

	void StartBoosting();
	void StopBoosting();
	bool bBoosting = false;
	float BoostAmount; // Boost Fuel
	float BoostPower; // Additive

	UFUNCTION(Category = "VehicleFunctions")
	void Shooting();



};
