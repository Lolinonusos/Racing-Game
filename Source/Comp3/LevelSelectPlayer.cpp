// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSelectPlayer.h"

// Sets default values
ALevelSelectPlayer::ALevelSelectPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelSelectPlayer::BeginPlay()
{
	Super::BeginPlay();
	EnableInput(GetWorld()->GetFirstPlayerController());
	
	//InputComponent->BindAction()
}

// Called every frame
void ALevelSelectPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelSelectPlayer::MoveCameraRight() {

}

void ALevelSelectPlayer::MoveCameraLeft() {

}

