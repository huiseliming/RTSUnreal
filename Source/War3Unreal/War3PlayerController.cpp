// Fill out your copyright notice in the Description page of Project Settings.


#include "War3PlayerController.h"
#include "War3CameraPawn.h"
#include "Kismet/GameplayStatics.h"

AWar3PlayerController::AWar3PlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void AWar3PlayerController::BeginPlay()
{
	Super::BeginPlay();
	FInputModeGameAndUI InputModeGameAndUI;
	InputModeGameAndUI.SetHideCursorDuringCapture(false);
	InputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	SetInputMode(InputModeGameAndUI);
}

void AWar3PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

FVector AWar3PlayerController::GetCursorWorldPlacement(float Distance)
{
	FVector WorldLocation, WorldDirection;
	DeprojectMousePositionToWorld(WorldLocation,WorldDirection);
	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit,WorldLocation,WorldLocation + Distance * WorldDirection, ECollisionChannel::ECC_Visibility))
	{
		return Hit.Location;
	}
	return FVector();
}
