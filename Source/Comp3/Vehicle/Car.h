// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

//#include <UObject/ConstructorHelpers.h>

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle")
	class UBoxComponent* CollisionBox = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle")
	class UBoxComponent* HoverBox = nullptr;

	// Create tracers
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle")
	class UHeightTracer_Component* TracerPointOne = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle")
	class UHeightTracer_Component* TracerPointTwo = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle")
	class UHeightTracer_Component* TracerPointThree = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle")
	class UHeightTracer_Component* TracerPointFour = nullptr;
	
	bool bInAir;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VehicleVariables")
	float DriveSpeed = 5000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VehicleVariables")
	float TurnSpeed = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VehicleVariables")
	float TurnHelp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VehicleVariables")
	float HoverHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VehicleVariables")
	int AmmoTotal = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VehicleVariables")
	int MaxAmmo = 50;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VehicleVariables")
	float BoostAmount = 5; // Boost Fuel
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VehicleVariables")
	float MaxBoostAmount = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VehicleVariables")
	float BoostPower = 10000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VehicleVariables")
		TArray<FString> SpecialWeaponsInventory;


	int GetAmmo();
	int GetBoost();
	int GetTotalBoost();
	
	FString GetSpecial();
	bool bTimerIsFinished = false;
	UPROPERTY(BlueprintReadWrite)
	bool bGameIsPaused = false;

	int ShotgunUses = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VehicleVariables")
	float MaxHealth = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VehicleVariables")
	float CurrentHealth = 10;
	UPROPERTY(BlueprintReadWrite)
	bool bIsInOptions = false;
	UPROPERTY(BlueprintReadWrite)
	bool bReadyToLeavePause = false;

	float GetTotalHealth();
	float GetCurrentHealth();

	float RespawnTime = 0;
	FTransform RespawnTransform;
	void KillTest();
	void Respawn();
	
	UFUNCTION(BlueprintCallable)
		void PauseGame();

	FTimerHandle RespawnTimer;
private:
	UPROPERTY(EditAnywhere, Category = "VehicleCamera")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "VehicleCamera")
	class UCameraComponent* BackCamera;

	UPROPERTY(EditAnywhere, Category = "VehicleCamera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = "VehicleCamera")
	class USpringArmComponent* BackSpringArm;

	UPROPERTY(EditAnywhere, Category = "VehicleMesh")
	class UStaticMeshComponent* VehicleMesh;

	UPROPERTY(EditAnywhere, Category = "VehicleParticles")
	class UParticleSystem* VehicleDeath;

	UPROPERTY(EditAnywhere, Category = "VehicleParticles")
	class UParticleSystem* BoostParticle;

	UPROPERTY(EditAnywhere, Category = "VehicleParticles")
	class UParticleSystem* BoostExhausted;
	
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

	

	void StartDriving();
	void StopDriving();
	bool bDriving = false;

	void StartBrake();
	void StopBrake();
	bool bBraking = false;
	
	void Turn(float AxisValue);
	float CurrentTurnSpeed;
	
	float CurrentYawRotation;
	float CurrentPitchRotation;
	float CurrentRollRotation;
	
	FRotator NeutralRotation;
	float RollAlpha = 0;
	float RollInterp = 0.f;
	void UpdateRoll(float Input);
	
	void StartBoosting();
	void StopBoosting();
	bool bBoosting = false;
	bool bBackCamera = false;
	
	
	float RefillTimer;
	
	UFUNCTION(Category = "VehicleFunctions")
	void Shooting();
	UFUNCTION(Category = "VehicleFunctions")
	void SpecialShooting();
	UFUNCTION(Category = "VehicleFunctions")
		void ChangeCamera();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> ActorToSpawn;
	
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, 
		UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, 
			const FHitResult &SweepResult);

	//TArray<class UCheckpointSceneComponent> LatestCheckpointVistited[1];

	// Respawn position should be a little higher than 

	
};
