// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpPadSceneComponent.h"
#include "Comp3/Vehicle/Car.h"
#include "Components/BoxComponent.h"

// Sets default values for this component's properties
UJumpPadSceneComponent::UJumpPadSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	JumpArea = CreateDefaultSubobject<UBoxComponent>(TEXT("JumpArea"));
	JumpArea->SetupAttachment(this);
	JumpArea->SetWorldScale3D(FVector(2.f, 2.f, 1.f));
}


// Called when the game starts
void UJumpPadSceneComponent::BeginPlay()
{
	Super::BeginPlay();

	RootComponentVariable = Cast<UBoxComponent>(GetOwner()->GetRootComponent());

	if(JumpArea)
	{
		JumpArea->OnComponentBeginOverlap.AddDynamic(this, &UJumpPadSceneComponent::OnOverlap);
	}
}


// Called every frame
void UJumpPadSceneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UJumpPadSceneComponent::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ACar::StaticClass()))
	{
		ACar* CarJumpPointer = Cast<ACar>(OtherActor);
		FVector JumpVector = CarJumpPointer->CollisionBox->GetUpVector();
		CarJumpPointer->CollisionBox->AddImpulse(JumpVector * 1000.f * CarJumpPointer->CollisionBox->GetMass());
	}
}

