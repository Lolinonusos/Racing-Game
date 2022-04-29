// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"
#include "Comp3/Comp3GameModeBase.h"
#include "Comp3/Vehicle/Car.h"
#include "Components/BoxComponent.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CheckpointBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CheckpointBox"));
	CheckpointBox->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckpoint::TurnOnCollision()
{
	CheckpointBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

}

void ACheckpoint::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ACar::StaticClass()))
	{
		AComp3GameModeBase* GameModePtr = Cast<AComp3GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		GameModePtr->CheckPointsReached += 1;
		CheckpointBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		ACar* CarPtr = Cast<ACar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		CurrentCheckpointPosition = GetActorLocation();
		UE_LOG(LogTemp, Warning, TEXT("Current checkpoint position is %f, %f, %f"), CurrentCheckpointPosition.X, CurrentCheckpointPosition.Y, CurrentCheckpointPosition.Z);

		CarPtr->RespawnTransform = GetActorTransform();
		
		// Re-enables collision when all checkpoints are reached
		if (GameModePtr->LapCleared())
		{
			CheckpointBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}

	}
}

