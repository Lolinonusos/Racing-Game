// Fill out your copyright notice in the Description page of Project Settings.


#include "Countdown.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Containers/Array.h"
#include <UObject/ConstructorHelpers.h>

// Sets default values
ACountdown::ACountdown()
{
	CountdownBallsArray.Init(NULL, 3);
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountdownText"));
	CountdownText->SetHorizontalAlignment(EHTA_Center);
	CountdownText->SetWorldSize(250.0f);
	CountdownText->SetTextRenderColor(FColor::Red);
	RootComponent = CountdownText;

	CountdownText->GetComponentLocation();

	//static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshCom(TEXT("D:/Unreal projects/Comp3/Content/Meshes/Temp/CountdownTimerBalls.uasset"));
	
	CountdownBall1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CountdownBall1"));
	CountdownBall2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CountdownBall2"));
	CountdownBall3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CountdownBall3"));

	CountdownBallsArray[0] = CountdownBall1;
	CountdownBallsArray[1] = CountdownBall2;
	CountdownBallsArray[2] = CountdownBall3;

	int ArraySize = CountdownBallsArray.Num();
	/*if (CountdownBall1) {
		for (int i = 0; i < ArraySize; i++) {
			CountdownBallsArray[i]->SetStaticMesh(SphereMeshCom.Object);
			UE_LOG(LogTemp, Warning, TEXT("check"));
		}
	}*/
	
	TimerTime = 3;
}

// Called when the game starts or when spawned
void ACountdown::BeginPlay()
{
	Super::BeginPlay();

	FVector Sphere1Location = CountdownText->GetComponentLocation();
	FVector Sphere2Location = CountdownText->GetComponentLocation();
	FVector Sphere3Location = CountdownText->GetComponentLocation();

	Sphere1Location.Y -= 200;
	Sphere1Location.Z += 300;

	Sphere2Location.Z += 300;

	Sphere3Location.Y += 200;
	Sphere3Location.Z += 300;


	CountdownBallsArray[0]->SetWorldLocation(Sphere1Location);
	CountdownBallsArray[1]->SetWorldLocation(Sphere2Location);
	CountdownBallsArray[2]->SetWorldLocation(Sphere3Location);

	CountdownText->SetText(FText::AsNumber(TimerTime));
	GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, this, &ACountdown::AdvanceTimer, 1.0f, true);
	UWorld* World = GetWorld();
	if (World) {
		UGameplayStatics::PlaySound2D(World, CountdownSound, 1.f, 1.f, 1.f);
	}

}

// Called every frame
void ACountdown::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACountdown::AdvanceTimer() {
	CountdownText->SetText(FText::AsNumber(TimerTime));
	if (TimerTime < 1) {
		//Countdown finished
		ACar* PlayerCar = Cast<ACar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		PlayerCar->bTimerIsFinished = true;

		AFollower* Follower = Cast<AFollower>(UGameplayStatics::GetActorOfClass(GetWorld(), FollowerActor));
		
		if (Follower) {
			Follower->bCanMove = true;
		}

		CountdownText->SetTextRenderColor(FColor::Green);
		CountdownText->SetText(INVTEXT("GO!"));
	} 
	if (TimerTime < 0) {
		GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
		Destroy();
	}
	TimerTime--;
	if (TimerTime >= 0 && TimerTime < 3) {
		CountdownBallsArray[TimerTime]->DestroyComponent();
	}
}