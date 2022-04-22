// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "JumpPadSceneComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMP3_API UJumpPadSceneComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJumpPadSceneComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	class UBoxComponent* RootComponentVariable;
	
	UPROPERTY()
	class UBoxComponent* JumpArea;
	
	UFUNCTION()
void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, 
UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, 
const FHitResult &SweepResult);
};
