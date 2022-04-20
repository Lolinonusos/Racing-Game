// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSelect.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ALevelSelect::ALevelSelect()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	Levels.Add("The Big Cheesus");
	Levels.Add("Broccoli Trees");

	sdsd = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("sdsd"));

	SetRootComponent(sdsd);

	LevelSelectSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("LevelSelectSpringArm"));

	

	LevelSelectCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("LevelSelectCamera"));
	LevelSelectCamera->SetupAttachment(LevelSelectSpringArm, USpringArmComponent::SocketName);
	//LevelSelectCamera->AddLocalOffset(FVector(0.0f, 0.0f, 60.0f));

	LevelSelectSpringArm->SetupAttachment(RootComponent);
	LevelSelectSpringArm->TargetArmLength = 500.f;
	LevelSelectSpringArm->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));
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

}

// Called to bind functionality to input
void ALevelSelect::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("Steer", this, &ALevelSelect::MoveCamera);
}

void ALevelSelect::MoveCamera(float AxisValue) {
	
	if (AxisValue > 0) {
		// Player is pressing D - Camera moves to the right
		
		if (Levels.IsValidIndex((RotationNumber + 1))) {
			RotationNumber++;
			sdsd->SetWorldLocation(FVector(-150, -150, -150));
			UE_LOG(LogTemp, Warning, TEXT("PRESSED D"));
		}
	}
	else if (AxisValue < 0) {
		// Player is pressing A - Camera moves to the left
		
		if (Levels.IsValidIndex((RotationNumber - 1))) {
			RotationNumber--;
			sdsd->SetWorldLocation(FVector(150, 150, 150));
			UE_LOG(LogTemp, Warning, TEXT("PRESSED A"));
		}
	}
}

