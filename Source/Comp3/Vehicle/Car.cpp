// Fill out your copyright notice in the Description page of Project Settings.

#include "Car.h"
#include "Bullet.h"
#include "../Non-Players/Follower.h"

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

// Pickups
#include "../Objects/Powerups/SpeedBoost.h"
#include "../Objects/Powerups/AmmoRefill.h"
#include "../Objects/Powerups/ItemPickups.h"
#include "../Objects/Powerups/HealthRefill.h"

// Objects
#include "../Objects/CheckPoint.h"
#include "../Objects/BoostPad.h"

#include "../HUDClass.h"



// Sets default values
ACar::ACar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);

	VehicleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VehicleMesh"));
	VehicleMesh->SetupAttachment(RootComponent);

	// HoverBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	// HoverBox->SetupAttachment(RootComponent);
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	BackSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("BackSpringArm"));

	CollisionBox->SetSimulatePhysics(true);
	
	//
	// CAMERAS
	// Back facing camera (Points forward)
	//
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->AddLocalOffset(FVector(0.0f, 0.0f, 60.0f));

	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 500.f;
	SpringArm->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;

	SpringArm->bUsePawnControlRotation = false;
	
	SpringArm->CameraLagSpeed = 3.f;
	SpringArm->CameraRotationLagSpeed = 3.f;
	SpringArm->CameraLagMaxDistance = 100.f;

	// Front facing camera (Points backwards)

	BackCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("BackCamera"));
	BackCamera->SetupAttachment(BackSpringArm, USpringArmComponent::SocketName);
	BackCamera->AddLocalOffset(FVector(0.0f, 0.0f, 60.0f));

	BackSpringArm->SetupAttachment(RootComponent);
	BackSpringArm->TargetArmLength = 500.f;
	BackSpringArm->SetRelativeRotation(FRotator(-20.f, 180.f, 0.f));
	BackSpringArm->bEnableCameraLag = true;
	BackSpringArm->bEnableCameraRotationLag = true;

	BackSpringArm->bUsePawnControlRotation = false;

	BackSpringArm->CameraLagSpeed = 3.f;
	BackSpringArm->CameraRotationLagSpeed = 3.f;
	BackSpringArm->CameraLagMaxDistance = 100.f;
	
	// End of camera stuff

	TracerPointOne = CreateDefaultSubobject<UHeightTracer_Component>(TEXT("TracerComponentOne"));
	TracerPointTwo = CreateDefaultSubobject<UHeightTracer_Component>(TEXT("TracerComponentTwo"));
	TracerPointThree = CreateDefaultSubobject<UHeightTracer_Component>(TEXT("TracerComponentThree"));
	TracerPointFour = CreateDefaultSubobject<UHeightTracer_Component>(TEXT("TracerComponentFour"));
	
	PawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> VehicleMeshComponent(TEXT("StaticMesh'/Game/Art_Assets/TempVehicle.TempVehicle'"));
	if (VehicleMeshComponent.Succeeded())
	{
		VehicleMesh->SetStaticMesh(VehicleMeshComponent.Object);
	}

	PawnMovementComponent->MaxSpeed = 5000.f;
	PawnMovementComponent->Deceleration = 1500.f;
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

	
	float MaxDistance = 200.f;
	FVector EndLocation = GetActorLocation() + (GetActorUpVector() * -MaxDistance);
    FHitResult HitResult;
	FCollisionObjectQueryParams CollisionObjectQueryParams;
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);

	DrawDebugLine(GetWorld(), VehicleMesh->GetComponentLocation()+ FVector(-30.f, -130.f,0.f), EndLocation - FVector(-30.f,-130.f,0.f), FColor(255.f,0.f,0.f), false, 1.f, 0, 5.f);

	DrawDebugLine(GetWorld(), VehicleMesh->GetComponentLocation()+ FVector(30.f, -130.f,0.f), EndLocation - FVector(30.f,-130.f,0.f), FColor(255.f,0.f,0.f), false, 1.f, 0, 5.f);

	DrawDebugLine(GetWorld(), VehicleMesh->GetComponentLocation()+ FVector(-30.f, 130.f,0.f), EndLocation - FVector(-30.f,-130.f,0.f), FColor(255.f,0.f,0.f), false, 1.f, 0, 5.f);

	DrawDebugLine(GetWorld(), VehicleMesh->GetComponentLocation()+ FVector(30.f, 130.f,0.f), EndLocation - FVector(30.f,-130.f,0.f), FColor(255.f,0.f,0.f), false, 1.f, 0, 5.f);
	
	if(GetWorld()->LineTraceSingleByObjectType(HitResult, VehicleMesh->GetComponentLocation(), EndLocation, CollisionObjectQueryParams))
	{
		//CollisionBox->AddForce(GetActorUpVector() * 10000.f * CollisionBox->GetMass());
		// FVector TraceOneNormal = HitResult.ImpactNormal * FVector(0.f, 0.f,1.f);
		// VehicleMesh->SetRelativeRotation(TraceOneNormal.Rotation());
		UE_LOG(LogTemp, Warning, TEXT("Tracer works"));
	}


	//FRotator NewRotation = FVector::Rotation(TraceOneNormal);
	
	// Movement
	FVector Forward = GetActorForwardVector();
	Forward.Z = 0;
	
	if (bBoosting)
	{
		BoostAmount -= 0.05f;
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
			if (BoostAmount < 3.f)
			{
				BoostAmount += 0.01f;
			}
		}
	}
	
	//UE_LOG(LogTemp, Warning, TEXT("Current BoostFuel: %f"), BoostAmount);
	
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
		CollisionBox->AddRelativeRotation(FRotator(0.f, 3.f, 0.f) * CurrentTurnSpeed);

		//float TargetTurnSpeed = AxisValue * TurnSpeed;
		//FVector Turning = FVector (0.f, 0.f, 100.f);
		//VehicleMesh->AddTorqueInRadians(Turning * TargetTurnSpeed * VehicleMesh->GetMass());

		if (bDriving)
		{
			// Jeg vet ikke koden her blir ubrukelig eller ikke :////

			//VehicleMesh->AddTorqueInRadians(TurnSpeed * VehicleMesh->GetMass());

			// Også gjør vi sånne yaw, pitch og roll inni her og tror jeg :))

		}
	}
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
	// This function is responsible for the logic behind shooting with a special item
	// The outer if sentence checks if the countdown timer at the beginning is finished
	// The inner one checks if the inventory item is a shootgun and checks if the player boosts
	// The player cannot fire a special item while they boost
	if (bTimerIsFinished) {
		if (SpecialWeaponsInventory[0] == "Shotgun" && bBoosting == false) {
			
			UWorld* tempWorld = GetWorld();
			if (tempWorld)
			{
				if (bBackCamera) {
					// Camera is in front, looking back, so the player is shooting backwards
					FVector Location = GetActorLocation();
					FVector FwdVector = GetActorForwardVector();
					FwdVector *= -200;
					Location += FwdVector;
					FRotator ShotgunRotation = GetActorRotation();
					ShotgunRotation.Yaw += 180; // This makes the bullets appear behind the player
					FRotator x(0, 2.5, 0);
					for (int i = 0; i < 5; i++) {
						tempWorld->SpawnActor<AActor>(ActorToSpawn, Location, (ShotgunRotation - 2 * x) + x * i);
					}
				}
				else {
					// Camera is in the default state, which means the player is shooting forwards
					FVector Location = GetActorLocation();
					FVector FwdVector = GetActorForwardVector();
					FwdVector *= 200;
					Location += FwdVector;
					FRotator x(0, 2.5, 0);
					for (int i = 0; i < 5; i++) {
						tempWorld->SpawnActor<AActor>(ActorToSpawn, Location, (GetActorRotation() - 2 * x) + x * i);
					}
				}
				// Regardless of camera  angle, uses of the shotgun will decrease by 1
				// It then checks if it should be removed from the inventory
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
	// This function changes camera angle from back to front
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
	
	// This if chain checks what hits the player, this line is for speed boost
	if (OtherActor->IsA(ASpeedBoost::StaticClass())) {
		Cast<ASpeedBoost>(OtherActor)->Super::DeleteSelf();
		if ((BoostAmount + 1) > MaxBoostAmount) {
			BoostAmount = 5;
		}
		else {
			BoostAmount++;
		}
	}
	// This line checks for ammo boxes
	else if (OtherActor->IsA(AAmmoRefill::StaticClass())) {
		AAmmoRefill* AmmoTemp = Cast<AAmmoRefill>(OtherActor);
		if ((AmmoTotal + AmmoTemp->GetAmmoRegen()) > MaxAmmo) {
			AmmoTotal = MaxAmmo;
		}
		else {
			AmmoTotal += AmmoTemp->GetAmmoRegen();
		}
		
		AmmoTemp->Super::DeleteSelf();
	}
	// This line checks for item pickups and checks if the player's inventory is full
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
	// This line checks for health pickups
	else if (OtherActor->IsA(AHealthRefill::StaticClass())) {
		AHealthRefill* tmp = Cast<AHealthRefill>(OtherActor);
		if ((CurrentHealth + tmp->GetHealthRegen()) > MaxHealth) {
			CurrentHealth = MaxHealth;
		}
		else {
			CurrentHealth += tmp->GetHealthRegen();
		}
		UE_LOG(LogTemp, Warning, TEXT("HEALTH: %f"), CurrentHealth);
		tmp->Super::DeleteSelf();
	}
	else if(OtherActor->IsA(ABoostPad::StaticClass()))
	{
		
	}
	// This checks if the player hit an enemy, currently it lowers health, will be changed later
	else if (OtherActor->IsA(AFollower::StaticClass())) {
		if ((CurrentHealth - 1) < 0) {
			CurrentHealth = 0;
		}
		else {
			CurrentHealth--;
		}
	}
}


//
// FUNCTIONS THAT RETURN THE VARIABLES THE HUD USES
//


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

