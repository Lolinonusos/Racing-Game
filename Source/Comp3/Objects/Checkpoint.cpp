// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"

#include "GameFramework/Actor.h"

#include "Comp3/Comp3GameModeBase.h"
#include "Comp3/Game-Logic/RacingGameInstance.h"
#include "Comp3/UI/GameHUD.h"
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

	AComp3GameModeBase* GameModePtr = Cast<AComp3GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameModePtr->SetTotalCheckPoints(1);

	if(bIsGoal)
	{
		SetActorEnableCollision(false);
	}
	
	if (CheckpointBox)
	{
		CheckpointBox->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlap);
	}
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AComp3GameModeBase* GameModePtr = Cast<AComp3GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GameModePtr->CheckPointsReached == (GameModePtr->TotalCheckPoints - 1) && this->bIsGoal)
	{
		//CheckpointBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		SetActorEnableCollision(true);
		UE_LOG(LogTemp, Warning, TEXT("Now goal should be active"));
	}
}

// Reset collision values
void ACheckpoint::TurnOnCollision()
{
	if(!bIsGoal)
	{
		SetActorEnableCollision(true);
	}
	else
	{
		SetActorEnableCollision(false);
	}
}

void ACheckpoint::GoThroughAllCheckpoints() {
	GetWorldTimerManager().ClearTimer(RegenCheckpoints);
	bCheckpointTimerIsActive = false;
	
	TArray<AActor*> Checkpoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACheckpoint::StaticClass(), Checkpoints);
	
	for (int i = 0; i < Checkpoints.Num(); i++) {
		if (Checkpoints[i])
		{
			Cast<ACheckpoint>(Checkpoints[i])->TurnOnCollision();
		}
	}
}

void ACheckpoint::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                            UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ACar::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("HIT CHECKPOINT"))
		AComp3GameModeBase* GameModePtr = Cast<AComp3GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		GameModePtr->CheckPointsReached += 1;
		SetActorEnableCollision(false);

		ACar* CarPtr = Cast<ACar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		CurrentCheckpointPosition = GetActorLocation();
		UE_LOG(LogTemp, Warning, TEXT("Current checkpoint position is %f, %f, %f"), CurrentCheckpointPosition.X, CurrentCheckpointPosition.Y, CurrentCheckpointPosition.Z);

		// Respawn coordinates
		CarPtr->RespawnLocation = GetActorLocation();
		CarPtr->RespawnRotation = GetActorRotation();

		// If Sentence by Joachim
		if (Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->ChosenGameModeToPlay == "Time") {
			Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD())->IncreaseTime("Checkpoint");
		}
		
	
		
		// Re-enables collision when all checkpoints are reached
		if (GameModePtr->LapCleared())
		{
			UE_LOG(LogTemp, Warning, TEXT("HAS GONE THROUGH ALL CHECKPOINTS"))
			CheckpointBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			
			if (!bCheckpointTimerIsActive) {
				bCheckpointTimerIsActive = true;
				if (Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->ChosenGameModeToPlay == "Shooter") {
					GoThroughAllCheckpoints();
				} else {
					GetWorldTimerManager().SetTimer(RegenCheckpoints, this, &ACheckpoint::GoThroughAllCheckpoints, 1.f, false, 3.f);
				}
			}
		}
	}
}

