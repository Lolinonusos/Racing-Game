// Fill out your copyright notice in the Description page of Project Settings.

#include "Car.h"
#include "Bullet.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"

#include "GameFramework/PawnMovementComponent.h"

// for force
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/PrimitiveComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Math/Vector.h"

// Sets default values
ACar::ACar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VehicleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VehicleMesh"));
	SetRootComponent(VehicleMesh);
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

	VehicleMesh->SetSimulatePhysics(true);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->AddLocalOffset(FVector(0.0f, 0.0f, 60.0f));
	
	SpringArm->SetupAttachment(VehicleMesh, USpringArmComponent::SocketName);
	SpringArm->TargetArmLength = 500.f;
	SpringArm->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	//SpringArm->PreviousDesiredLoc
	//SpringArm->PreviousDesiredRot
	
	SpringArm->CameraLagSpeed = 3.f;
	SpringArm->CameraRotationLagSpeed = 3.f;
	SpringArm->CameraLagMaxDistance = 100.f;
	
	PawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> VehicleMeshComponent(TEXT("StaticMesh'/Game/Meshes/TempVehicle.TempVehicle'"));
	if (VehicleMeshComponent.Succeeded())
	{
		VehicleMesh->SetStaticMesh(VehicleMeshComponent.Object);
	}

}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector Forward = GetActorForwardVector();

	if (bBoosting)
	{
	 	BoostAmount -= 0.05f;
		VehicleMesh->AddForce(Forward * BoostPower * VehicleMesh->GetMass());
	}
	
	if (!bBoosting)
	{
		if (BoostAmount < 3)
		{
	 		BoostAmount += 0.01f;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Current BoostFuel: %f"), BoostAmount);

	
	if (bDriving)
	{
		// 	FMath::FInterpTo(DriveSpeed, 5.f, DeltaTime, 1.f);
		// }
		//AddMovementInput(GetActorForwardVector(), FMath::FInterpTo(DriveSpeed, 5.f, DeltaTime, 1.f) + BoostPower );

		VehicleMesh->AddForce(Forward * DriveSpeed * VehicleMesh->GetMass());
		
		UE_LOG(LogTemp, Warning, TEXT("Forward"));
		
	}

	if (bBraking)
	{
		VehicleMesh->AddForce(Forward * (-DriveSpeed/2) * VehicleMesh->GetMass());
		UE_LOG(LogTemp, Warning, TEXT("Backward"));
	}


}

// Called to bind functionality to input
void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Moves forward
	InputComponent->BindAction("Drive", IE_Pressed, this, &ACar::StartDriving);
	InputComponent->BindAction("Drive", IE_Released, this, &ACar::StopDriving);

	// Moves backward
	InputComponent->BindAction("Brake", IE_Pressed, this, &ACar::StartBrake);
	InputComponent->BindAction("Brake", IE_Released, this, &ACar::StopBrake);

	InputComponent->BindAction("Boost", IE_Pressed, this, &ACar::StartBoosting);
	InputComponent->BindAction("Boost", IE_Released, this, &ACar::StopBoosting);
	
	// Rotate Player
	InputComponent->BindAxis("Steer", this, &ACar::Turn);

}

void ACar::StartDriving()
{
	bDriving = true;
}

void ACar::StopDriving()
{
	bDriving = false;
}

void ACar::StartBrake()
{
	bBraking = true;
}

void ACar::StopBrake()
{
	bBraking = false;
}

void ACar::Turn(float AxisValue)
{
	// Rotation
	//AddControllerYawInput(AxisValue * TurnSpeed);
	AddActorLocalRotation(FRotator(0.f, AxisValue, 0.f));
    if (AxisValue > 0.f)
    {
    	UE_LOG(LogTemp, Warning, TEXT("Turning"));
    }

	// FRotator CurrentRotation = GetActorRotation();
	//
	// FMath::FInterpTo(CurrentRotation, AxisValue, )
	
}

void ACar::StartBoosting()
{
	// Add boost power to forward movement
	// Should push forward when not driving
	if (BoostAmount > 0) 
	{
		bBoosting = true;
	}
}

void ACar::StopBoosting()
{
	bBoosting = false;
}

void ACar::Shooting()
{




}


