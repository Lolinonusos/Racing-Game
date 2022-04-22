// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSelect.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Math/UnrealMathVectorCommon.h"

// Sets default values
ALevelSelect::ALevelSelect()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FPlanet Level1;
	Level1.PlanetName = "The Big Cheesus";
	Level1.IdealCameraRotation = FRotator(0, 0, 0);
	Level1.IdealCameraLocation= FVector(-80, 0, 0);

	FPlanet Level2;
	Level2.PlanetName = "Broccoli Trees";
	Level2.IdealCameraRotation = FRotator(0, -90, 0);
	Level2.IdealCameraLocation = FVector(400, 480, 0);

	FPlanet Level3;
	Level3.PlanetName = "Level 3";
	Level3.IdealCameraRotation = FRotator(0, 90, 0);
	Level3.IdealCameraLocation = FVector(400, -480, 0);
	
	Levels.Add(Level1);
	Levels.Add(Level2);
	Levels.Add(Level3);
	UE_LOG(LogTemp, Warning, TEXT("Level Name: %s"), *Levels[RotationNumber].PlanetName);

	sdsd = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("sdsd"));

	SetRootComponent(sdsd);

	LevelSelectSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("LevelSelectSpringArm"));

	

	LevelSelectCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("LevelSelectCamera"));
	LevelSelectCamera->SetupAttachment(LevelSelectSpringArm, USpringArmComponent::SocketName);
	//LevelSelectCamera->AddLocalOffset(FVector(0.0f, 0.0f, 60.0f));

	LevelSelectSpringArm->SetupAttachment(RootComponent);
	LevelSelectSpringArm->TargetArmLength = 200.f;
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
	//UE_LOG(LogTemp, Warning, TEXT("Level Name: %s"), *Levels[RotationNumber].PlanetName);
	if (bStartingToLerp) {
		if (bMovingRight) {
			Alpha += CameraChangeSpeed;
			
			SetActorLocation(FMath::Lerp(GetActorLocation(), Levels[RotationNumber].IdealCameraLocation, Alpha));
			SetActorRotation(FMath::Lerp(GetActorRotation(), Levels[RotationNumber].IdealCameraRotation, Alpha));

			if (Alpha >= 1) {
				bStartingToLerp = false;
			}
		}
		else {
			Alpha -= CameraChangeSpeed;

			SetActorLocation(FMath::Lerp(GetActorLocation(), Levels[RotationNumber].IdealCameraLocation, Alpha));
			SetActorRotation(FMath::Lerp(GetActorRotation(), Levels[RotationNumber].IdealCameraRotation, Alpha));
			
			if (Alpha <= 0) {
				bStartingToLerp = false;
			}
		}
		
	}

}

// Called to bind functionality to input
void ALevelSelect::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction("SelectLeft", IE_Pressed, this, &ALevelSelect::MoveCameraLeft);
	InputComponent->BindAction("SelectRight", IE_Pressed, this, &ALevelSelect::MoveCameraRight);
	InputComponent->BindAction("Select", IE_Pressed, this, &ALevelSelect::SelectLevel);
}

void ALevelSelect::MoveCameraLeft() {
	if (Levels.IsValidIndex((RotationNumber - 1))) {
		RotationNumber--;
		bMovingRight = false;
		bStartingToLerp = true;
	}
}

void ALevelSelect::MoveCameraRight() {
	if (Levels.IsValidIndex((RotationNumber + 1))) {
		RotationNumber++;
		UE_LOG(LogTemp, Warning, TEXT("Level Name: %s"), *Levels[RotationNumber].PlanetName);
		bMovingRight = true;
		bStartingToLerp = true;
	}
}

void ALevelSelect::SelectLevel() {
	
	if (Levels[RotationNumber].PlanetName == "The Big Cheesus") {
		UGameplayStatics::OpenLevel(GetWorld(), "Test");
		
	}
	else if (Levels[RotationNumber].PlanetName == "Broccoli Trees") {
		
	}
}

