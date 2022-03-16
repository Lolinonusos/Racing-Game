// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class COMP3_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(EditAnywhere, Category = "BulletVariables")
	float TravelSpeed = 6000.f;

	UPROPERTY(EditAnywhere, Category = "BulletVariables")
	float SecondsLived;
	
	UPROPERTY(EditAnywhere, Category = "BulletVariables")
	float DeleteAfter = 3.f;

	UPROPERTY(EditAnywhere, Category = "Bullet")
	class UStaticMeshComponent* BulletMesh;

	UPROPERTY(EditAnywhere, Category = "Bullet")
	class USoundBase* SpawnSound;
	
	UPROPERTY(EditAnywhere, Category = "Bullet")
	class USoundBase* DeleteSound;

	UPROPERTY(EditAnywhere, Category = "Bullet")
	class UParticleSystem* MuzzleFlash;
	
	UPROPERTY(EditAnywhere, Category = "Bullet")
	class UParticleSystem* HitSpark;
	
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int32 OtherbodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
