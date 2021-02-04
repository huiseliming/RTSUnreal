// Fill out your copyright notice in the Description page of Project Settings.


#include "War3Unit.h"

// Sets default values
AWar3Unit::AWar3Unit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWar3Unit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWar3Unit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWar3Unit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

