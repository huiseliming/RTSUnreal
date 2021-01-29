// Fill out your copyright notice in the Description page of Project Settings.


#include "War3CameraPawn.h"

// Sets default values
AWar3CameraPawn::AWar3CameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWar3CameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWar3CameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWar3CameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

