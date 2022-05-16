// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSelect.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Math/UnrealMathVectorCommon.h"

// THIS DOCUMENT WAS WRITTEN BY JOACHIM

// Sets default values
ALevelSelect::ALevelSelect()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FPlanet Level1;
	Level1.PlanetName = "The Big Cheesus";
	Level1.IdealCameraRotation = FRotator(0, 0, 0);
	Level1.IdealCameraLocation= FVector(-100, 0, 0);
	Level1.FocusedCameraLocation = GetActorLocation();
	Level1.FocusedCameraLocation.X = Level1.IdealCameraLocation.X + 50;
	Level1.FocusedCameraLocation.Y = Level1.IdealCameraLocation.Y + 100;
	Level1.FocusedCameraLocation.Z = Level1.IdealCameraLocation.Z - 50;
	Level1.bCanFocus = true;

	FPlanet Level2;
	Level2.PlanetName = "NOT YET IMPLEMENTED";
	Level2.IdealCameraRotation = FRotator(0, -90, 0);
	Level2.IdealCameraLocation = FVector(400, 500, 0);
	Level2.FocusedCameraLocation = GetActorLocation();
	Level2.FocusedCameraLocation.X = Level2.IdealCameraLocation.X + 100;
	Level2.FocusedCameraLocation.Y = Level2.IdealCameraLocation.Y - 50;
	Level2.FocusedCameraLocation.Z = Level2.IdealCameraLocation.Z - 50;
	Level2.bCanFocus = false;

	FPlanet Level3;
	Level3.PlanetName = "NOT YET IMPLEMENTED";
	Level3.IdealCameraRotation = FRotator(0, 180, 0);
	Level3.IdealCameraLocation = FVector(900, 0, 0);
	Level3.FocusedCameraLocation = GetActorLocation();
	Level3.FocusedCameraLocation.X = Level3.IdealCameraLocation.X - 50;
	Level3.FocusedCameraLocation.Y = Level3.IdealCameraLocation.Y - 100;
	Level3.FocusedCameraLocation.Z = Level3.IdealCameraLocation.Z - 50;
	Level3.bCanFocus = false;
	
	
	FPlanet Level4;
	Level4.PlanetName = "NOT YET IMPLEMENTED";
	Level4.IdealCameraRotation = FRotator(0, 90, 0);
	Level4.IdealCameraLocation = FVector(400, -500, 0);
	Level4.FocusedCameraLocation = GetActorLocation();
	Level4.FocusedCameraLocation.X = Level4.IdealCameraLocation.X - 100;
	Level4.FocusedCameraLocation.Y = Level4.IdealCameraLocation.Y + 50;
	Level4.FocusedCameraLocation.Z = Level4.IdealCameraLocation.Z - 50;
	Level4.bCanFocus = false;

	Levels.Add(Level1);
	Levels.Add(Level2);
	Levels.Add(Level3);
	Levels.Add(Level4);



	UE_LOG(LogTemp, Warning, TEXT("Level Name: %s"), *Levels[RotationNumber].PlanetName);

	//sdsd = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("sdsd"));

	//SetRootComponent(sdsd);

	LevelSelectSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("LevelSelectSpringArm"));

	

	LevelSelectCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("LevelSelectCamera"));
	LevelSelectCamera->SetupAttachment(LevelSelectSpringArm, USpringArmComponent::SocketName);

	LevelSelectSpringArm->SetupAttachment(RootComponent);
	LevelSelectSpringArm->TargetArmLength = 250.f;
	LevelSelectSpringArm->bEnableCameraLag = true;
	LevelSelectSpringArm->bEnableCameraRotationLag = true;

	LevelSelectSpringArm->bUsePawnControlRotation = false;

	LevelSelectSpringArm->CameraLagSpeed = 3.f;
	LevelSelectSpringArm->CameraRotationLagSpeed = 3.f;
	LevelSelectSpringArm->CameraLagMaxDistance = 100.f;
}

// Called when the game starts or when spawned
void ALevelSelect::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALevelSelect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bStartingToLerp) {
		if (bMovingRight) {
			Alpha += GetWorld()->GetDeltaSeconds();
			
			SetActorLocation(FMath::Lerp(GetActorLocation(), Levels[RotationNumber].IdealCameraLocation, Alpha));
			SetActorRotation(FMath::Lerp(GetActorRotation(), Levels[RotationNumber].IdealCameraRotation, Alpha));

			if (Alpha >= 1) {
				Alpha = 0;
				bPausedControls = false;
				bStartingToLerp = false;
			}
		}
		else {
			Alpha -= GetWorld()->GetDeltaSeconds();

			SetActorLocation(FMath::Lerp(GetActorLocation(), Levels[RotationNumber].IdealCameraLocation, Alpha));
			SetActorRotation(FMath::Lerp(GetActorRotation(), Levels[RotationNumber].IdealCameraRotation, Alpha));
			
			if (Alpha <= 0) {
				Alpha = 0;
				bPausedControls = false;
				bStartingToLerp = false;
			}
		}
	}

	if (bIsEnteringFocus && Levels[RotationNumber].bCanFocus && (bIsLeavingFocus == false)) {
		FocusAlpha += GetWorld()->GetDeltaSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("New Location: %s"), *Levels[RotationNumber].FocusedCameraLocation.ToString());
		SetActorLocation(FMath::Lerp(GetActorLocation(), Levels[RotationNumber].FocusedCameraLocation, FocusAlpha));
		
		if (FocusAlpha >= 1) {
			FocusAlpha = 1;
			bIsEnteringFocus = false;
		}
	}
	if (bIsLeavingFocus && (bIsEnteringFocus == false)) {
		FocusAlpha -= GetWorld()->GetDeltaSeconds();
		SetActorLocation(FMath::Lerp(GetActorLocation(), Levels[RotationNumber].IdealCameraLocation, FocusAlpha));
		
		if (FocusAlpha <= 0) {
			FocusAlpha = 0;
			bIsLeavingFocus = false;
		}
	}
}

// Called to bind functionality to input
void ALevelSelect::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction("SelectLeft", IE_Pressed, this, &ALevelSelect::MoveCameraLeft);
	InputComponent->BindAction("SelectRight", IE_Pressed, this, &ALevelSelect::MoveCameraRight);
	//InputComponent->BindAction("Select", IE_Pressed, this, &ALevelSelect::SelectLevel);
}

void ALevelSelect::MoveCameraLeft() {
	if (Levels.IsValidIndex((RotationNumber - 1))) {
		RotationNumber--;
	}
	else {
		RotationNumber = (Levels.Num() - 1);
	}
	bPausedControls = true;
	//UE_LOG(LogTemp, Warning, TEXT("Level Name: %s"), *Levels[RotationNumber].PlanetName);
	bMovingRight = true;
	bStartingToLerp = true;	
}

void ALevelSelect::MoveCameraRight() {
	if (Levels.IsValidIndex((RotationNumber + 1))) {
		RotationNumber++;
	}
	else {
		RotationNumber = 0;
	}
	bPausedControls = true;
	//UE_LOG(LogTemp, Warning, TEXT("Level Name: %s"), *Levels[RotationNumber].PlanetName);
	bMovingRight = true;
	bStartingToLerp = true;
}

void ALevelSelect::SelectLevel() {
	bIsEnteringFocus = true;
}

