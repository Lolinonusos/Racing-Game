// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Comp3/Comp3GameModeBase.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Checkpoint_Component.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMP3_API UCheckpoint_Component : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCheckpoint_Component();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditInstanceOnly, Category = "CheckpointVariables")
	bool bIsGoal = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checkpoint")
	class UStaticMeshComponent* CheckpointMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CheckpointBox")
	class UBoxComponent* CheckpointBox;
	

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, 
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, 
		const FHitResult &SweepResult);
};
