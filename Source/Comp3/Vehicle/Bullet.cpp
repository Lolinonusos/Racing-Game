// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Car.h"
#include "Comp3/Non-Players/Follower.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	BulletMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	BulletMesh->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlap);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorForwardVector() * TravelSpeed * DeltaTime;
	SetActorLocation(NewLocation);

	SecondsLived += DeltaTime;
	if (SecondsLived >= DeleteAfter) {
		this->Destroy();
	}
}

void ABullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherbodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Bullet collided"));
	// if it hits an enemy actor destroy enemy and this actor 
	if (OtherActor->IsA(AFollower::StaticClass()))
	{
		// Runs the hit function in Alien.cpp
		Cast<AFollower>(OtherActor)->ImHit();

		// Particles
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BulletFire, GetTransform(), true);

		// SoundFX
		//UGameplayStatics::PlaySoundAtLocation(GetWorld(), BulletSound, GetActorLocation());
		UWorld* World = GetWorld();
		//UGameplayStatics::PlaySound2D(World, BulletHit, 1.f, 1.f, 0.f, 0);


		
		
		// Destroy Bullet
		Destroy();
	}
}