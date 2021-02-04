// Fill out your copyright notice in the Description page of Project Settings.


#include "War3PlayerController.h"

#include "War3Unit.h"
#include "GameFramework/HUD.h"
#include "Kismet/GameplayStatics.h"

AWar3PlayerController::AWar3PlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void AWar3PlayerController::ActionInputMousePressed()
{
	if (GetMousePosition(MouseClickedPos.X, MouseClickedPos.Y))
	{
		MouseHoldingPos.X = MouseClickedPos.X;
		MouseHoldingPos.Y = MouseClickedPos.Y;
		bIsMouseClicked = true;
	}
}

void AWar3PlayerController::ActionInputMouseReleased()
{
	bIsMouseClicked = false;
	if((MouseHoldingPos - MouseClickedPos).Size() > 3.0f)
		DragSelect();
	else
		SimpleSelect();
}

void AWar3PlayerController::SimpleSelect()
{
	TArray<AWar3Unit*> SelectedUnits;
	//GLog->Log(TEXT("AWar3PlayerController::SimpleSelect()"));
}

void AWar3PlayerController::DragSelect()
{
	TArray<AWar3Unit*> SelectedUnits;
	//GLog->Log(TEXT("AWar3PlayerController::DragSelect()"));
}

void AWar3PlayerController::BeginPlay()
{
	Super::BeginPlay();
	// Setup InputMode
	FInputModeGameAndUI InputModeGameAndUI;
	InputModeGameAndUI.SetHideCursorDuringCapture(false);
	InputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	SetInputMode(InputModeGameAndUI);
}

void AWar3PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AWar3PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// if (InputComponent == nullptr)
	// {
	// 	InputComponent = NewObject<UInputComponent>(this,"InputComponent");
	// 	InputComponent->RegisterComponent();
	// }
	InputComponent->BindAction(TEXT("LeftMouseClick"), EInputEvent::IE_Pressed, this, &AWar3PlayerController::ActionInputMousePressed);
	InputComponent->BindAction(TEXT("LeftMouseClick"), EInputEvent::IE_Released, this, &AWar3PlayerController::ActionInputMouseReleased);
}

FVector AWar3PlayerController::GetCursorWorldPlacement(const float Distance)
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

