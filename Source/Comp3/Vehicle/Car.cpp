// Fill out your copyright notice in the Description page of Project Settings.

#include "Car.h"
#include "Bullet.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"

#include "GameFramework/PawnMovementComponent.h"
#include "Engine/World.h"

#include "GameFramework/FloatingPawnMovement.h"

// for force
#include "Components/PrimitiveComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Math/Vector.h"

#include "../Objects/Powerups/SpeedBoost.h"
#include "../Objects/Powerups/AmmoRefill.h"
#include "../Objects/Powerups/ItemPickups.h"

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
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->AddLocalOffset(FVector(0.0f, 0.0f, 60.0f));

	BackCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("BackCamera"));
	BackCamera->SetupAttachment(BackSpringArm, USpringArmComponent::SocketName);
	BackCamera->AddLocalOffset(FVector(0.0f, 0.0f, 60.0f));

	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 500.f;
	SpringArm->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;

	SpringArm->bUsePawnControlRotation = false;
	
	SpringArm->CameraLagSpeed = 3.f;
	SpringArm->CameraRotationLagSpeed = 3.f;
	SpringArm->CameraLagMaxDistance = 100.f;

	BackSpringArm->SetupAttachment(RootComponent);
	BackSpringArm->TargetArmLength = 500.f;
	BackSpringArm->SetRelativeRotation(FRotator(-20.f, 180.f, 0.f));
	BackSpringArm->bEnableCameraLag = true;
	BackSpringArm->bEnableCameraRotationLag = true;

	BackSpringArm->bUsePawnControlRotation = false;

	BackSpringArm->CameraLagSpeed = 3.f;
	BackSpringArm->CameraRotationLagSpeed = 3.f;
	BackSpringArm->CameraLagMaxDistance = 100.f;

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
	
	if (ScreenWidget) {
		MainWidget = CreateWidget<UUserWidget>(AActor::GetWorld(), ScreenWidget);
	}
	
	/*MainWidget->AddToViewport(); 
	MainWidget->SetVisibility(ESlateVisibility::Visible);*/

}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TracerPointOne->GetDistance();
	// TracerPointTwo->GetDistance();
	// TracerPointThree->GetDistance();
	// TracerPointFour->GetDistance();

	
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

	FVector Forward = GetActorForwardVector();
	FVector Right = GetActorRightVector();
	
	// Gir smooth
	CurrentTurnSpeed = FMath::FInterpTo(CurrentTurnSpeed, AxisValue, GetWorld()->GetDeltaSeconds(), 1.f);
	//FMath::Clamp(TargetTurnSpeed, -200.f, 200.f);
	CollisionBox->AddRelativeRotation(FRotator(0.f, 3.f,0.f) * CurrentTurnSpeed);

	//float TargetTurnSpeed = AxisValue * TurnSpeed;
	//FVector Turning = FVector (0.f, 0.f, 100.f);
	//VehicleMesh->AddTorqueInRadians(Turning * TargetTurnSpeed * VehicleMesh->GetMass());
	
	if (bDriving)
	{
		// Jeg vet ikke koden her blir ubrukelig eller ikke :////
		
		//VehicleMesh->AddForce(Turning * TurnSpeed * VehicleMesh->GetMass());
		
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

