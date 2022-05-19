// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowerCharacter.h"

#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "Comp3/Comp3GameModeBase.h"
#include "Comp3/Game-Logic/RacingGameInstance.h"
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
	PlayerCheck->InitSphereRadius(5000.f);
	
	GetCharacterMovement()->MaxAcceleration = 2000.f;
	GetCharacterMovement()->MaxWalkSpeed = 1200.f;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
}

// Called when the game starts or when spawned
void AFollowerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (!AIController)
	{
		AIController = Cast<AAIController>(GetController());
	} 
	

	// Count enemies that exist
	AComp3GameModeBase* GameModePtr = Cast<AComp3GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameModePtr->EnemiesAlive += 1;
	
	
	if (PlayerCheck)
	{
		UE_LOG(LogTemp, Warning, TEXT("Entered the player check"))
		PlayerCheck->OnComponentBeginOverlap.AddDynamic(this, &AFollowerCharacter::OnOverlap);
	}

	// GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AFollowerCharacter::OnOverlap);
}

// Called every frame
void AFollowerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DespawnTimer <= 0.f)
	{
		Despawn();
	}

	if (AIController)
	{
		AIController->MoveToActor(Cast<ACar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)));
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("COULD NOT FIND AI CONTROLLER"))
	}

	if (GetPlayerDistance() <=  2000.f)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.f;
		
		// Backs away from player
		FVector GoBackwards = GetActorLocation();
		GoBackwards += GetActorForwardVector() * -1000.f * DeltaTime;
		SetActorLocation(GoBackwards);
		
		bIsNearPlayer = true;
	}
	else if (GetPlayerDistance() >=  2000.f)
	{
		GetCharacterMovement()->MaxAcceleration = 2000.f;
		GetCharacterMovement()->MaxWalkSpeed = 1200.f;

		bIsNearPlayer = true;
	}
	else if (GetPlayerDistance() >= 6000.f)
	{
		GetCharacterMovement()->MaxAcceleration = 6000.f;
		GetCharacterMovement()->MaxWalkSpeed = 2000.f;

		
		ShootTimer = 3.f;
		bIsNearPlayer = false;
	}

	Shoot();
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
	if (bIsNearPlayer)
	{
		ShootTimer -= 0.01;
		if (ShootTimer <= 0.f)
		{
			ShootTimer = 3.f;
			
			ACar* PlayerPtr = Cast<ACar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
			FVector PlayerLocation = PlayerPtr->GetActorLocation();

			FVector AimAtPlayer = PlayerLocation - GetActorLocation();
			
			FRotator EnemyRotation = AimAtPlayer.Rotation();
			SetActorRotation(EnemyRotation);

			UWorld* World = GetWorld();
			if (World)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), ShootingSound, Cast<URacingGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetGameAudio(), 1.f, 0.f, nullptr, nullptr, true);
				World->SpawnActor<AActor>(SpawnBullet, GetActorLocation(), GetActorRotation());
				UE_LOG(LogTemp, Warning, TEXT("AI did the shooty"));

			}
		}
		
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
		//bIsNearPlayer = true;
		// Needs navmesh to function
		//UE_LOG(LogTemp, Warning, TEXT("Enemy sensed player"));
		//GetWorldTimerManager().SetTimer(ShootTimer, this, &AFollowerCharacter::Shoot, 3.f, true, 3.f);
	}

	if (IsValid(OtherActor))
	{
		if (OtherActor->IsA(ABullet::StaticClass()))
		{
			Cast<ABullet>(OtherActor)->Destroy(); // Destroy the bullet
			ImHit(); // -1 health for this
			if (Health <= 0)
			{
				Despawn();
			}
			UE_LOG(LogTemp, Warning, TEXT("Am hurt"));
	
		}
	}
}

