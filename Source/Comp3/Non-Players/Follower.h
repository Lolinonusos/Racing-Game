// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

	bool IsHit{ false };

	FVector MoveDirection = FVector(1.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere)
		float Speed{ 20.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FollowerMesh")
		class UStaticMeshComponent* FollowerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FollowerMesh")
		class UMaterial* FollowerMaterial;


};
