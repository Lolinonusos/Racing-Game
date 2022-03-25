// Fill out your copyright notice in the Description page of Project Settings.


#include "Follower.h"
#include "Components/SkeletalMeshComponent.h"

#include "Components/BoxComponent.h"


// Sets default values
AFollower::AFollower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);
	
	FollowerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FollowerMesh"));
	FollowerMesh->SetupAttachment(CollisionBox);

	FollowerMaterial = CreateDefaultSubobject<UMaterial>(TEXT("FollowerMaterial"));

	

}

// Called when the game starts or when spawned
void AFollower::BeginPlay()
{
	Super::BeginPlay();
	PlayerCarPtr = Cast<ACar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

}

// Called every frame
void AFollower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	MoveDirection = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - GetActorLocation();
	
	SetActorRotation(MoveDirection.Rotation());

	//FVector NewLocation = GetActorLocation();

	if(CollisionBox)
	{
		if (PlayerCarPtr->bTimerIsFinished) {
			CollisionBox->AddRelativeLocation(GetActorForwardVector() * Speed);
		}
	}
	
	//SetActorLocation(NewLocation);
	// if(MoveDirection.Size() < 50.f)
	// {
	// 	// bFortnite = true;
	// }
}

void AFollower::ImHit()
{
	UE_LOG(LogTemp, Warning, TEXT("Follower got hit"));
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	this->Destroy();
	IsHit = true;
}