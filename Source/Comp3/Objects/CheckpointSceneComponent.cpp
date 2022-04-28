// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointSceneComponent.h"
#include "Comp3/Comp3GameModeBase.h"
#include "Comp3/Vehicle/Car.h"
#include "Components/BoxComponent.h"

// Sets default values for this component's properties
UCheckpointSceneComponent::UCheckpointSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CheckpointBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CheckpointBox"));
	CheckpointBox->SetupAttachment(this);
}


// Called when the game starts
void UCheckpointSceneComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (!bIsGoal)
	{
		if (CheckpointBox)
		{
			CheckpointBox->OnComponentBeginOverlap.AddDynamic(this, &UCheckpointSceneComponent::OnOverlap);
			//CheckpointBox->OnComponentEndOverlap.AddDynamic(this, &UCheckpointSceneComponent::OnComponentEndOverlap);
		}
	}
	
	AComp3GameModeBase* GameModePtr = Cast<AComp3GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameModePtr->SetTotalCheckPoints(1);
}

// Called every frame
void UCheckpointSceneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UCheckpointSceneComponent::TurnOnCollision()
{
	CheckpointBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void UCheckpointSceneComponent::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ACar::StaticClass()))
	{
		AComp3GameModeBase* GameModePtr = Cast<AComp3GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		GameModePtr->CheckPointsReached += 1;
		CheckpointBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CurrentCheckpointPosition = GetComponentLocation();
		UE_LOG(LogTemp, Warning, TEXT("Current checkpoint position is %f, %f, %f"), CurrentCheckpointPosition.X, CurrentCheckpointPosition.Y, CurrentCheckpointPosition.Z);
	}
}

// void UCheckpointSceneComponent::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
// 	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
// {
// 	if (OtherActor->IsA(ACar::StaticClass()))
// 	{
// 		AComp3GameModeBase* GameModePtr = Cast<AComp3GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
// 		GameModePtr->CheckPointsReached += 1;
// 		CheckpointBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//
// 	}
// }

