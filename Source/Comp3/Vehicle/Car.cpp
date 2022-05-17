// Fill out your copyright notice in the Description page of Project Settings.

#include "Car.h"
#include "Bullet.h"
#include "../Non-Players/Follower.h"
#include "HeightTracer_Component.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// for Movement
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/PrimitiveComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Math/Vector.h"
#include "Math/Rotator.h"

// Objects
#include "../UI/GameHUD.h"
#include "../Game-Logic/RacingGameInstance.h"

// Timer
#include "TimerManager.h"

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
	CurrentWeapon.WeaponName = "Shotgun";
	CurrentWeapon.WeaponUses = 2;
	CollisionBox = this->FindComponentByClass<UBoxComponent>();

	if (CollisionBox) {
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACar::OnOverlap);
	}

	// First SpawnPoint
    RespawnLocation = GetActorLocation();
	RespawnRotation = GetActorRotation();

	
	if (Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->ChosenGameModeToPlay == "Time") {
		SetActorRotation(FRotator(0, 180, 0));
		bIsInTimeTrialMode = true;
	}
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


	// Slow down when driving on offroad
	FVector EndLocation = GetActorLocation() + (GetActorUpVector() * - 150);
	FCollisionObjectQueryParams CollisionObjectQueryParams;
	// Uses offroad collision channel
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel1);
	FHitResult HitResult;
	// Hit something
	if (GetOwner()->GetWorld()->LineTraceSingleByObjectType(HitResult, GetActorLocation(), EndLocation, CollisionObjectQueryParams))
	{
		UE_LOG(LogTemp, Warning, TEXT("I am offroad :)"));
		PawnMovementComponent->MaxSpeed = 1500.f;
		if (bDriving || bBraking)
		{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OffRoadParticles, GetTransform(), true);

		// 	FRotator OffRoadShake;
		//
		// 	OffRoadShake.Roll = 10.f * (FMath::Sin(DeltaTime));
		//
		// 	VehicleMesh->SetRelativeRotation(OffRoadShake);
		// }
		// else
		// {
		// 	VehicleMesh->SetRelativeRotation(FRotator(GetActorForwardVector().Rotation()));
		}
	}
	else
	{
		PawnMovementComponent->MaxSpeed = 2500.f;
	}
		
	// Movement
	FVector Forward = VehicleMesh->GetForwardVector();
	Forward.Z = 0;
	
	if (bBoosting)
	{
		BoostAmount -= 0.01f;
		CollisionBox->AddForce(Forward * BoostPower * CollisionBox->GetMass());
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BoostParticle, GetTransform(), true);
		if (BoostAmount < 0.f)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BoostExhausted, GetTransform(), true);
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

	CollisionObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	// Gravity
	if (GetOwner()->GetWorld()->LineTraceSingleByObjectType(HitResult, GetActorLocation(), EndLocation, CollisionObjectQueryParams))
	{
		CollisionBox->SetLinearDamping(2.f);
	}
	else
	{
		CollisionBox->SetLinearDamping(0.01);
	}
	
	if (CurrentHealth <= 0)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), VehicleDeath, GetTransform(), true);

		CurrentHealth = MaxHealth;


		SetActorTickEnabled(false);
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		// Call Respawn() after 2 seconds 
		GetWorldTimerManager().SetTimer(RespawnTimer, this, &ACar::Respawn, 1.f, false, 2.f);

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

	// Pausing
	InputComponent->BindAction("Pause", IE_Pressed, this, &ACar::PauseGame).bExecuteWhenPaused = true;
	// Respawn testing
	InputComponent->BindAction("KillSelf", IE_Pressed, this, &ACar::KillTest);

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
// Function written by Joachim
void ACar::Shooting()
{
	FRotator Rotation = GetActorRotation();
	if (bTimerIsFinished && (bIsInTimeTrialMode == false)) {
		if (AmmoTotal > 0 && bBoosting == false) {
			UWorld* World = GetWorld();
			if (World)
			{
				if (bBackCamera) {
					// Shooting backwards
					GetProjectilePlacement(true);
					Rotation.Yaw += 180;
				}
				else {
					// Shooting forwards
					GetProjectilePlacement(false);
				}
				Rotation.Pitch += 3;
				World->SpawnActor<AActor>(ActorToSpawn, BulletSpawnLocation, Rotation);
				AmmoTotal--;
			}
		}
	}
	
}
// Function written by Joachim
void ACar::SpecialShooting() 
{
	UWorld* tempWorld = GetWorld();
	if (bTimerIsFinished && (bIsInTimeTrialMode == false)) {
		if (!bBoosting) {
			if (CurrentWeapon.WeaponName == "Shotgun") {
				FRotator ShotgunRotation = GetActorRotation();

				if (tempWorld)
				{
					if (bBackCamera) {
						// Shooting backwards
						GetProjectilePlacement(true);
						ShotgunRotation.Yaw += 180;
						ShotgunRotation.Pitch += 3;
					}
					else {
						GetProjectilePlacement(false);
						ShotgunRotation.Pitch += 3;
					}

					FRotator x(0, 2.5, 0);
					for (int i = 0; i < 5; i++) {
						tempWorld->SpawnActor<AActor>(ActorToSpawn, BulletSpawnLocation, (ShotgunRotation - 2 * x) + x * i);
					}

					CurrentWeapon.WeaponUses--;
					if (CurrentWeapon.WeaponUses == 0) {
						CurrentWeapon.WeaponName = "";
					}
				}
			}
		}
	}	
}
// Function written by Joachim
void ACar::ChangeCamera()
{
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
	if (OtherActor->IsA(AItemPickups::StaticClass())) {
		if (CurrentWeapon.WeaponName == "") {
			FWeapon BufferWeapon = Cast<AItemPickups>(OtherActor)->UniqueItems[0];
			if (BufferWeapon.WeaponName == "Shotgun") {
				CurrentWeapon = BufferWeapon;
			}
		}
		
		Cast<AItemPickups>(OtherActor)->Super::DeleteSelf();
	} else if (OtherActor->IsA(AFollower::StaticClass())) {
		CurrentHealth--;
	}
}

void ACar::KillTest()
{
	CurrentHealth = 0;
}

void ACar::Respawn()
{
	CurrentHealth = MaxHealth;
	//SetActorTransform(RespawnTransform);
	SetActorLocation(RespawnLocation);
	SetActorRotation(RespawnRotation);
	
	SetActorTickEnabled(true);
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);

	
	
	//Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD())->ShowFinishScreen();

	GetWorldTimerManager().ClearTimer(RespawnTimer);
	// SetActorLocation(RespawnPosition);
	// SetActorRotation(RespawnRotation);
}

void ACar::GetProjectilePlacement(bool bIsLookingBack) {
	BulletSpawnLocation = GetActorLocation();
	FVector FwdVector = GetActorForwardVector();

	if (bIsLookingBack) {
		FwdVector *= -200;
	}
	else {
		FwdVector *= 200;
	}

	BulletSpawnLocation += FwdVector;
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
	FString a = CurrentWeapon.WeaponName;
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

// Function written by Joachim
void ACar::PauseGame() {
	UE_LOG(LogTemp, Warning, TEXT("ENTERED PAUSE FUNCTION"))
	AGameHUD* HUDPtr = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (HUDPtr) {
		if (bGameIsPaused == false) {
			HUDPtr->OpenPauseMenu();
			bReadyToLeavePause = true;
			UGameplayStatics::SetGamePaused(GetWorld(), true);
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
		}
		else {			
			HUDPtr->ClosePauseMenu();
			bGameIsPaused = false;
			UGameplayStatics::SetGamePaused(GetWorld(), false);
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;	
		}
	}
}