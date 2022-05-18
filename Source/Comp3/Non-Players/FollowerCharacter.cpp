// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowerCharacter.h"

#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "Comp3/Comp3GameModeBase.h"
#include "Comp3/Vehicle/Bullet.h"
#include "Comp3/Vehicle/Car.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GamePlayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
//#include "AIController.h"

// Sets default values
AFollowerCharacter::AFollowerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshComponent(TEXT("StaticMesh'/Game/Meshes/Enemy/PoliceHovercraft.PoliceHovercraft'"));
	if (StaticMesh)
	{
		StaticMesh->SetStaticMesh(StaticMeshComponent.Object);
	}
	
	PlayerCheck = CreateDefaultSubobject<USphereComponent>(TEXT("PlayerCheck"));
	PlayerCheck->SetupAttachment(GetRootComponent());
	// PlayerCheck->InitSphereRadius(5000.f);
	
	GetCharacterMovement()->MaxAcceleration = 2000.f;
}

// Called when the game starts or when spawned
void AFollowerCharacter::BeginPlay()
{
	Super::BeginPlay();

	AIController = Cast<AAIController>(GetController());

	// Count enemies that exist
	AComp3GameModeBase* GameModePtr = Cast<AComp3GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameModePtr->EnemiesAlive += 1;
	
	//if (PlayerCheck)
	//{
		PlayerCheck->OnComponentBeginOverlap.AddDynamic(this, &AFollowerCharacter::OnOverlap);
		PlayerCheck->OnComponentEndOverlap.AddDynamic(this, &AFollowerCharacter::OnOverlapEnd);
	//}

	// GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AFollowerCharacter::OnOverlap);

	// ACar* Player = Cast<ACar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	// if(Player)
	// {
	// 	AIController->MoveToActor(Player, -1);
	// }
}

// Called every frame
void AFollowerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DespawnTimer <= 0.f)
	{
		Despawn();
	}

	GetPlayerDistance();
	//UE_LOG(LogTemp, Warning, TEXT("Distance from player %f"), GetPlayerDistance());
	// if (GetPlayerDistance() >= 10000.f)
	// {
	// 	GetCharacterMovement()->MaxFlySpeed = 8000.f;
	// 	
	// 	DespawnTimer -= 0.01f;
	// }
	// if (GetPlayerDistance() >= 5000.f)
	// {
	// 	GetCharacterMovement()->MaxFlySpeed = 5000.f;
	// }
	// else
	// {
	// 	GetCharacterMovement()->MaxFlySpeed = 2000.f;
	// 	DespawnTimer = 7.f;
	// }
	
}

float AFollowerCharacter::GetPlayerDistance()
{
	ACar* PlayerPtr = Cast<ACar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	FVector EndLocation = PlayerPtr->GetActorLocation();
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECC_GameTraceChannel2);
	
	if(GetWorld()->LineTraceSingleByObjectType(HitResult, GetActorLocation(), EndLocation, CollisionObjectQueryParams))
	{
		DrawDebugLine(GetWorld(), GetActorLocation(), EndLocation, FColor::Green, false, 0.1f, 0, 5.f);

		return(HitResult.Location - GetActorLocation()).Size();
	}
	return 1.f;
}

void AFollowerCharacter::Shoot()
{
	FRotator EnemyRotation = GetActorRotation();
	UWorld* World = GetWorld();
	if (World)
	{
		//World->SpawnActor<AActor>();
	}
}

void AFollowerCharacter::ImHit()
{
	Health -= 1;
	if (Health <= 0)
	{
		// Increase score
		
		Despawn();
	}
}

void AFollowerCharacter::Despawn()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	AComp3GameModeBase* GameModePtr = Cast<AComp3GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	UE_LOG(LogTemp, Warning, TEXT("Am dead"));
	GameModePtr->EnemiesAlive -= 1;
	this->Destroy();
}

void AFollowerCharacter::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ACar::StaticClass()))
	{
		//ACar* Player = Cast<ACar>(OtherActor);
		AIController->MoveToActor(OtherActor, -1);
		bIsNearPlayer = true;
		// Needs navmesh to function
		UE_LOG(LogTemp, Warning, TEXT("Enemy sensed player"));
		//GetWorldTimerManager().SetTimer(ShootTimer, this, &AFollowerCharacter::Shoot, 3.f, true, 3.f);
	}

	if (OtherActor->IsA(ABullet::StaticClass()))
	{
	 	Cast<ABullet>(OtherActor)->Destroy(); // Destroy the bullet
	 	ImHit(); // -1 health for this
		UE_LOG(LogTemp, Warning, TEXT("Am hurt"));

	}
}

void AFollowerCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	
	bIsNearPlayer = false;
}

