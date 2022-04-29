// Fill out your copyright notice in the Description page of Project Settings.

#include "Car.h"
#include "Bullet.h"
#include "../Non-Players/Follower.h"
#include "HeightTracer_Component.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

// for Movement
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/PrimitiveComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Math/Vector.h"
#include "Math/Rotator.h"

// Pickups
#include "../Objects/Powerups/SpeedBoost.h"
#include "../Objects/Powerups/AmmoRefill.h"
#include "../Objects/Powerups/ItemPickups.h"

// Objects

#include "../HUDClass.h"
#include "Physics/ImmediatePhysics/ImmediatePhysicsShared/ImmediatePhysicsCore.h"


// Sets default values
ACar::ACar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);

	VehicleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VehicleMesh"));
	VehicleMesh->SetupAttachment(GetRootComponent());

	// HoverBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	// HoverBox->SetupAttachment(RootComponent);
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	BackSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("BackSpringArm"));

	CollisionBox->SetSimulatePhysics(true);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->AddLocalOffset(FVector(0.0f, 0.0f, 60.0f));
	
	BackCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("BackCamera"));
	BackCamera->SetupAttachment(BackSpringArm, USpringArmComponent::SocketName);
	BackCamera->AddLocalOffset(FVector(0.0f, 0.0f, 60.0f));

	SpringArm->SetupAttachment(VehicleMesh);
	SpringArm->SetupAttachment(GetRootComponent());

	SpringArm->TargetArmLength = 500.f;
	SpringArm->SetRelativeRotation(FRotator(-5.f, 0.f, 0.f));
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;

	SpringArm->bUsePawnControlRotation = false;
	
	SpringArm->CameraLagSpeed = 3.f;
	SpringArm->CameraRotationLagSpeed = 3.f;
	SpringArm->CameraLagMaxDistance = 100.f;

	BackSpringArm->SetupAttachment(RootComponent);
	BackSpringArm->TargetArmLength = 500.f;
	BackSpringArm->SetRelativeRotation(FRotator(-5.f, 180.f, 0.f));
	BackSpringArm->bEnableCameraLag = true;
	BackSpringArm->bEnableCameraRotationLag = true;

	BackSpringArm->bUsePawnControlRotation = false;

	BackSpringArm->CameraLagSpeed = 3.f;
	BackSpringArm->CameraRotationLagSpeed = 3.f;
	BackSpringArm->CameraLagMaxDistance = 100.f;

	TracerPointOne = CreateDefaultSubobject<UHeightTracer_Component>(TEXT("TracerComponentOne"));
	TracerPointOne->SetupAttachment(GetRootComponent());
	//TracerPointOne->SetRelativeLocation(FVector(60.f, 30.f, 0.f));

	TracerPointTwo = CreateDefaultSubobject<UHeightTracer_Component>(TEXT("TracerComponentTwo"));
	TracerPointTwo->SetupAttachment(GetRootComponent());
	//TracerPointTwo->SetRelativeLocation(FVector(60.f, -30.f, 0.f));

	TracerPointThree = CreateDefaultSubobject<UHeightTracer_Component>(TEXT("TracerComponentThree"));
	TracerPointThree->SetupAttachment(GetRootComponent());
	//TracerPointThree->SetRelativeLocation(FVector(-60.f, 30.f, 0.f));

	TracerPointFour = CreateDefaultSubobject<UHeightTracer_Component>(TEXT("TracerComponentFour"));
	TracerPointFour->SetupAttachment(GetRootComponent());
	//TracerPointFour->SetRelativeLocation(FVector(-60.f, -30.f, 0.f));

	PawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));


	//StaticMesh'/Game/Placeholders/car/mouse_car.mouse_car'
	// StaticMesh'/Game/Art_Assets/TempVehicle.TempVehicle'
	static ConstructorHelpers::FObjectFinder<UStaticMesh> VehicleMeshComponent(TEXT("StaticMesh'/Game/Placeholders/car/player_car.player_car'"));
	if (VehicleMeshComponent.Succeeded())
	{
		VehicleMesh->SetStaticMesh(VehicleMeshComponent.Object);
	}

	PawnMovementComponent->MaxSpeed = 2500.f;
	PawnMovementComponent->Deceleration = 1500.f;
	
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
	
	/*if (ScreenWidget) {
		MainWidget = CreateWidget<UUserWidget>(AActor::GetWorld(), ScreenWidget);
	}*/
	
	/*MainWidget->AddToViewport(); 
	MainWidget->SetVisibility(ESlateVisibility::Visible);*/

}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CollisionBox->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);

	CurrentPitchRotation = CollisionBox->GetRelativeRotation().Pitch;
	CurrentPitchRotation = FMath::Clamp(CurrentPitchRotation, -10.f, 10.f);
	CurrentYawRotation = CollisionBox->GetRelativeRotation().Yaw;
	CurrentRollRotation = CollisionBox->GetRelativeRotation().Roll;
	CurrentRollRotation = FMath::Clamp(CurrentRollRotation, -30.f, 30.f);
	
	CollisionBox->SetRelativeRotation(FRotator(CurrentPitchRotation, CurrentYawRotation, CurrentRollRotation));
	
	// Movement
	FVector Forward = VehicleMesh->GetForwardVector();
	Forward.Z = 0;
	
	if (bBoosting)
	{
		BoostAmount -= 0.01f;
		CollisionBox->AddForce(Forward * BoostPower * CollisionBox->GetMass());
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
			if (BoostAmount < 5.f)
			{
				BoostAmount += 0.01f;
			}
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Current BoostFuel: %f"), BoostAmount);
	
	if (bDriving)
	{
		//CollisionBox->AddForce(Forward * DriveSpeed * CollisionBox->GetMass());
		//UE_LOG(LogTemp, Warning, TEXT("Forward"));

		AddMovementInput(FVector(Forward), DriveSpeed);
	}

	if (bBraking)
	{
		//CollisionBox->AddForce(Forward * (-DriveSpeed/2) * CollisionBox->GetMass());
		//UE_LOG(LogTemp, Warning, TEXT("Backward"));

		AddMovementInput(FVector(Forward), (-DriveSpeed/2));
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
	if (bTimerIsFinished) {
		bDriving = true;
	}
}

void ACar::StopDriving()
{
	bDriving = false;
}

void ACar::StartBrake()
{
	if (bTimerIsFinished) {
		bBraking = true;
	}
}

void ACar::StopBrake()
{
	bBraking = false;
}

void ACar::Turn(float AxisValue)
{
	// Rotation

	FVector Forward = GetActorForwardVector();
	FVector Right = GetActorRightVector();
	
	if (bTimerIsFinished) {
		// Gir smooth
		CurrentTurnSpeed = FMath::FInterpTo(CurrentTurnSpeed, AxisValue, GetWorld()->GetDeltaSeconds(), 1.f);
		//FMath::Clamp(TargetTurnSpeed, -200.f, 200.f);
		CollisionBox->AddRelativeRotation(FRotator(0.f, 5.f, 0.f) * CurrentTurnSpeed);

		//float TargetTurnSpeed = AxisValue * TurnSpeed;
		//FVector Turning = FVector (0.f, 0.f, 100.f);
		//VehicleMesh->AddTorqueInRadians(Turning * TargetTurnSpeed * VehicleMesh->GetMass());

		 if (bDriving)
		{
		 	// Roll only happens when you are driving
			UpdateRoll(AxisValue);
			//VehicleMesh->AddTorqueInRadians(TurnSpeed * VehicleMesh->GetMass());
	
		}
	}
}

void ACar::UpdateRoll(float Input)
{
	
	float RollTarget = 10.f;
	
	// Gradual tilt
	RollInterp = FMath::FInterpTo(RollInterp, (Input * RollTarget), GetWorld()->GetDeltaSeconds(), 1.f);
	
	RollInterp = FMath::Clamp(RollInterp, -RollTarget, RollTarget);

	//UE_LOG(LogTemp, Warning , TEXT("%f"), RollInterp);
	
	VehicleMesh->SetRelativeRotation(FRotator(0.f,0.f,10.f)* RollInterp);
	

	FRotator CurrentRoll = VehicleMesh->GetRelativeRotation();
		
	//RollAlpha = GetWorld()->DeltaTimeSeconds;
	//FMath::Lerp(0.f, TargetRoll, GetWorld()->DeltaTimeSeconds);
}

void ACar::StartBoosting()
{
	// Add boost power to forward movement
	// Should push forward when not driving
	if (bTimerIsFinished) {
		if (BoostAmount > 0)
		{
			bBoosting = true;
		}
	}
	
}

void ACar::StopBoosting()
{
	RefillTimer = 0.f;
	bBoosting = false;
}

void ACar::Shooting()
{
	if (bTimerIsFinished) {
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
	
}

void ACar::SpecialShooting() 
{
	if (bTimerIsFinished) {
		if (SpecialWeaponsInventory[0] == "Shotgun" && bBoosting == false) {
			
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
						tempWorld->SpawnActor<AActor>(ActorToSpawn, Location, (ShotgunRotation - 2 * x) + x * i);
					}
				}
				else {
					FVector Location = GetActorLocation();
					FVector FwdVector = GetActorForwardVector();
					FwdVector *= 200;
					Location += FwdVector;
					FRotator x(0, 2.5, 0);
					for (int i = 0; i < 5; i++) {
						tempWorld->SpawnActor<AActor>(ActorToSpawn, Location, (GetActorRotation() - 2 * x) + x * i);
					}
				}
				ShotgunUses--;
				if (ShotgunUses == 0) {
					SpecialWeaponsInventory[0] = "";
				}	
			}
		}
		else {

		}
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
			if (ChosenItem == "Shotgun") {
				ShotgunUses = 2;
			}
		}
		
		Cast<AItemPickups>(OtherActor)->Super::DeleteSelf();
	}

	else if (OtherActor->IsA(AFollower::StaticClass())) {
		CurrentHealth--;

	}
}

void ACar::Respawn()
{
	

	// SetActorLocation(RespawnPosition);
	// SetActorRotation(RespawnRotation);
}

int ACar::GetAmmo() {
	return AmmoTotal;
}

int ACar::GetBoost() {
	return BoostAmount;
}

int ACar::GetTotalBoost() {
	return MaxBoostAmount;
}

FString ACar::GetSpecial()
{
	FString a = SpecialWeaponsInventory[0];
	return a;
}

float ACar::GetTotalHealth()
{
	return MaxHealth;
}

float ACar::GetCurrentHealth()
{
	return CurrentHealth;
}

