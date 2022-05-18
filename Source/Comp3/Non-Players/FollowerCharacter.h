// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FollowerCharacter.generated.h"

//class AAIController;

UCLASS()
class COMP3_API AFollowerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFollowerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Called to bind functionality to input
	// virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* PlayerCheck;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
	class AAIController* AIController{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Particles")
	class UParticleSystem* DeathParticle;
	
	int Health = 3;
		
	bool bIsNearPlayer = false;
	float DespawnTimer = 7.f;

	FHitResult HitResult;
	FCollisionObjectQueryParams CollisionObjectQueryParams;
	float GetPlayerDistance();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> SpawnBullet;

	FTimerHandle ShootTimer;
	
	void Shoot();

	void ImHit();
	
	void Despawn();
	
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);
};


