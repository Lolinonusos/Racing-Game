// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Vehicle/Car.h"
#include "Kismet/GameplayStatics.h"
#include "Follower.generated.h"

UCLASS()
class COMP3_API AFollower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFollower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ImHit();
	float ReturnCurrentHealth();
	float ReturnMaxHealth();

	bool IsHit{ false };
	float CurrentHealth = 5.f;
	float MaxHealth = 5.f;

	FVector MoveDirection = FVector(1.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FollowerVariables")
		float Speed = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FollowerMesh")
	class UBoxComponent* CollisionBox = nullptr;
	
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "FollowerMesh")
	class USkeletalMeshComponent* FollowerMesh = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FollowerMesh")
	class UMaterial* FollowerMaterial = nullptr;

	bool bCanMove = false;
	ACar* PlayerCarPtr = nullptr; 
private:
	

};
