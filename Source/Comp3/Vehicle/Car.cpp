// Fill out your copyright notice in the Description page of Project Settings.

#include "Car.h"
#include "Bullet.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"

#include "GameFramework/PawnMovementComponent.h"
#include "Engine/World.h"

// for force
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/PrimitiveComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Math/Vector.h"

#include "../Objects/Powerups/SpeedBoost.h"
#include "../Objects/Powerups/AmmoRefill.h"
#include "../Objects/Powerups/ItemPickups.h"



// Sets default values
ACar::ACar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VehicleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VehicleMesh"));
	SetRootComponent(VehicleMesh);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	
	//UWorld::LineTraceSingleByChannel();

	// HoverBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	// HoverBox->SetupAttachment(RootComponent);
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	BackSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("BackSpringArm"));

	VehicleMesh->SetSimulatePhysics(true);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->AddLocalOffset(FVector(0.0f, 0.0f, 60.0f));

	BackCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("BackCamera"));
	BackCamera->SetupAttachment(BackSpringArm, USpringArmComponent::SocketName);
	BackCamera->AddLocalOffset(FVector(0.0f, 0.0f, 60.0f));

	SpringArm->SetupAttachment(VehicleMesh, USpringArmComponent::SocketName);
	SpringArm->TargetArmLength = 500.f;
	SpringArm->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;

	SpringArm->bUsePawnControlRotation = false;
	
	SpringArm->CameraLagSpeed = 3.f;
	SpringArm->CameraRotationLagSpeed = 3.f;
	SpringArm->CameraLagMaxDistance = 100.f;

	BackSpringArm->SetupAttachment(VehicleMesh, USpringArmComponent::SocketName);
	BackSpringArm->TargetArmLength = 500.f;
	BackSpringArm->SetRelativeRotation(FRotator(-20.f, 180.f, 0.f));
	BackSpringArm->bEnableCameraLag = true;
	BackSpringArm->bEnableCameraRotationLag = true;

	BackSpringArm->bUsePawnControlRotation = false;

	BackSpringArm->CameraLagSpeed = 3.f;
	BackSpringArm->CameraRotationLagSpeed = 3.f;
	BackSpringArm->CameraLagMaxDistance = 100.f;
	
	PawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> VehicleMeshComponent(TEXT("StaticMesh'/Game/Art_Assets/TempVehicle.TempVehicle'"));
	if (VehicleMeshComponent.Succeeded())
	{
		VehicleMesh->SetStaticMesh(VehicleMeshComponent.Object);
	}

	
//VehicleMesh->SetMassOverrideInKg()
	
}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();
	SpecialWeaponsInventory.Add("Shotgun");
	CollisionBox = this->FindComponentByClass<UBoxComponent>();

	if (CollisionBox) {
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACar::OnOverlap);
	}
	
}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult LineHit;
	FVector LineOneStart = GetActorLocation();


	
	FVector Forward = GetActorForwardVector();
	Forward.Z = 0;
	
	if (bBoosting)
	{
		BoostAmount -= 0.05f;
		VehicleMesh->AddForce(Forward * BoostPower * VehicleMesh->GetMass());
		if (BoostAmount < 0.f)
		{
			bBoosting = false;
		}
	}
	
	if (!bBoosting)
	{
		RefillTimer += 0.01f;
		if (RefillTimer >= 1.f)
		{
			if (BoostAmount < 3.f)
			{
				BoostAmount += 0.01f;
			}
		}
	}
	
	//UE_LOG(LogTemp, Warning, TEXT("Current BoostFuel: %f"), BoostAmount);
	
	if (bDriving)
	{
		VehicleMesh->AddForce(Forward * DriveSpeed * VehicleMesh->GetMass());
		//UE_LOG(LogTemp, Warning, TEXT("Forward"));
	}

	if (bBraking)
	{
		VehicleMesh->AddForce(Forward * (-DriveSpeed/2) * VehicleMesh->GetMass());
		//UE_LOG(LogTemp, Warning, TEXT("Backward"));
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

	// Adds boostpower as force to current force
	InputComponent->BindAction("Boost", IE_Pressed, this, &ACar::StartBoosting);
	InputComponent->BindAction("Boost", IE_Released, this, &ACar::StopBoosting);
	
	// Rotate Player
	InputComponent->BindAxis("Steer", this, &ACar::Turn);

	// Shooting
	InputComponent->BindAction("Shoot", IE_Pressed, this, &ACar::Shooting);
	InputComponent->BindAction("Special", IE_Pressed, this, &ACar::SpecialShooting);

	// Camera
	InputComponent->BindAction("SwitchCameraAngle", IE_Pressed, this, &ACar::ChangeCamera);

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
	
	// float Clamped =	FMath::Clamp(AxisValue * TurnSpeed, -45.f, 45.f);

	// Bruke torque?????

	
	
	//VehicleMesh->AddTorqueInRadians(Torqueing * AxisValue * VehicleMesh->GetMass());
	
	float TargetTurnSpeed = AxisValue * TurnSpeed;

	// Gir smooth
	CurrentTurnSpeed = FMath::FInterpTo(CurrentTurnSpeed, TargetTurnSpeed, GetWorld()->GetDeltaSeconds(), 1.f);
	AddActorLocalRotation(FRotator(0.f, CurrentTurnSpeed, 0.f));

	if (bDriving)
	{
		// Jeg vet ikke koden her blir ubrukelig eller ikke :////
		FVector Turning = FVector (0.f, 1.f, 0.f);
		
		VehicleMesh->AddForce(Turning * TurnSpeed * VehicleMesh->GetMass());

		// Også gjør vi sånne yaw, pitch og roll inni her og tror jeg :))
		
	}
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
	RefillTimer = 0.f;
	bBoosting = false;
}

void ACar::Shooting()
{
	
	if (AmmoTotal > 0 && bBoosting == false) {
		UWorld* World = GetWorld();
		if (World)
		{
			if (bBackCamera) {
				// Shooting backwards
				FVector Location = GetActorLocation();
				FVector FwdVector = GetActorForwardVector();
				FwdVector *= -200;
				Location += FwdVector;
				FRotator Rotation = GetActorRotation();
				Rotation.Yaw += 180;
				
				World->SpawnActor<AActor>(ActorToSpawn, Location, Rotation);
				AmmoTotal--;
			}
			else {
				// Shooting forwards
				FVector Location = GetActorLocation();
				FVector FwdVector = GetActorForwardVector();
				FwdVector *= 200;
				Location += FwdVector;
				World->SpawnActor<AActor>(ActorToSpawn, Location, GetActorRotation());
				AmmoTotal--;
			}
			
			
		}
	}
}

void ACar::SpecialShooting() 
{
	if (SpecialWeaponsInventory[0] == "Shotgun") {
		UWorld* tempWorld = GetWorld();
		if (tempWorld)
		{
			if (bBackCamera) {
				// Shooting backwards
				FVector Location = GetActorLocation();
				FVector FwdVector = GetActorForwardVector();
				FwdVector *= -200;
				Location += FwdVector;
				FRotator ShotgunRotation = GetActorRotation();
				ShotgunRotation.Yaw += 180;
				FRotator x(0, 2.5, 0);
				for (int i = 0; i < 5; i++) {
					tempWorld->SpawnActor<AActor>(ShotgunSpawn, Location, (ShotgunRotation - 2 * x) + x * i);
				}
			}
			else {
				FVector Location = GetActorLocation();
				FVector FwdVector = GetActorForwardVector();
				FwdVector *= 200;
				Location += FwdVector;
				FRotator x(0, 2.5, 0);
				for (int i = 0; i < 5; i++) {
					tempWorld->SpawnActor<AActor>(ShotgunSpawn, Location, (GetActorRotation() - 2 * x) + x * i);
				}
			}
			
			SpecialWeaponsInventory[0] = "";
		}
	}
	else {
		
	}
}

void ACar::ChangeCamera()
{
	UE_LOG(LogTemp, Warning, TEXT("ENTERED"))
	if (!bBackCamera) {
		Camera->Deactivate();
		BackCamera->Activate();
		
	}
	else {
		Camera->Activate();
		BackCamera->Deactivate();
	}
	bBackCamera = !bBackCamera;
	
}

void ACar::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor->IsA(ASpeedBoost::StaticClass())) {
		Cast<ASpeedBoost>(OtherActor)->Super::DeleteSelf();
		if ((BoostAmount + 1) > MaxBoostAmount) {
			BoostAmount = 5;
		}
		else {
			BoostAmount++;
		}
	}
	else if (OtherActor->IsA(AAmmoRefill::StaticClass())) {
		Cast<AAmmoRefill>(OtherActor)->Super::DeleteSelf();
		AmmoTotal += 30;
	}
	else if (OtherActor->IsA(AItemPickups::StaticClass())) {
		FString ChosenItem = "";
		if (SpecialWeaponsInventory[0] == "") {
			ChosenItem = Cast<AItemPickups>(OtherActor)->UniqueItems[0];
			SpecialWeaponsInventory[0] = ChosenItem;
		}
		
		Cast<AItemPickups>(OtherActor)->Super::DeleteSelf();
	}
}


