// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"

#include "Comp3/Comp3GameModeBase.h"
#include "Comp3/Non-Players/FollowerCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GamePlayStatics.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnPoint = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnPoint"));
	SetRootComponent(SpawnPoint);

	PlayerSenseSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PlayerSenseSphere"));
	PlayerSenseSphere->SetupAttachment(GetRootComponent());
	PlayerSenseSphere->InitSphereRadius(7500.f);
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerSenseSphere)
	{
		PlayerSenseSphere->OnComponentBeginOverlap.AddDynamic(this, &ASpawner::OnOverlap);
		PlayerSenseSphere->OnComponentEndOverlap.AddDynamic(this, &ASpawner::OnOverlapEnd);

	}
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AComp3GameModeBase* GameModePtr = Cast<AComp3GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameModePtr->EnemiesAlive >= 10)
	{
		GetWorldTimerManager().ClearTimer(SpawnTimer);
		UE_LOG(LogTemp, Warning, TEXT("10 bois in this world!"));
	}
}

void ASpawner::SpawnActor()
{
	UWorld* World = GetWorld();
	if (World)
	{
		World->SpawnActor<AFollowerCharacter>(SpawnAI, GetActorLocation(), GetActorRotation());
	}
}

void ASpawner::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawner::SpawnActor, 1.f, true, 5.f);
	UE_LOG(LogTemp, Warning, TEXT("Time to get the bois"));
}

void ASpawner::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	GetWorldTimerManager().ClearTimer(SpawnTimer);
	UE_LOG(LogTemp, Warning, TEXT("We'll get'em next time!"));
}

