// Fill out your copyright notice in the Description page of Project Settings.


#include "BoostPad.h"

#include "Comp3/Vehicle/Car.h"
#include "Components/BoxComponent.h"


// Sets default values
ABoostPad::ABoostPad()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(GetRootComponent());
	SetRootComponent(MeshComponent);
	
	BoostArea = CreateDefaultSubobject<UBoxComponent>(TEXT("BoostArea"));
	BoostArea->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ABoostPad::BeginPlay()
{
	Super::BeginPlay();

	if(BoostArea)
	{
		BoostArea->OnComponentBeginOverlap.AddDynamic(this, &ABoostPad::OnOverlap);
	}
	
}

// Called every frame
void ABoostPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoostPad::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ACar::StaticClass()))
	{
		ACar* CarBoostPointer = Cast<ACar>(OtherActor);
		FVector Forward = CarBoostPointer->CollisionBox->GetForwardVector();
		CarBoostPointer->CollisionBox->AddImpulse(Forward * 1000.f * CarBoostPointer->CollisionBox->GetMass());
	}
}

