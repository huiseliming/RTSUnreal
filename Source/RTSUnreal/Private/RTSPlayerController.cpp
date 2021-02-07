// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSPlayerController.h"

#include "RTSUnit.h"
#include "GameFramework/HUD.h"
#include "Kismet/GameplayStatics.h"

ARTSPlayerController::ARTSPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void ARTSPlayerController::ActionInputMousePressed()
{
	if (GetMousePosition(MouseClickedPos.X, MouseClickedPos.Y))
	{
		MouseHoldingPos.X = MouseClickedPos.X;
		MouseHoldingPos.Y = MouseClickedPos.Y;
		bIsMouseClicked = true;
	}
}

void ARTSPlayerController::ActionInputMouseReleased()
{
	bIsMouseClicked = false;
	if((MouseHoldingPos - MouseClickedPos).Size() > 3.0f)
		DragSelect();
	else
		SimpleSelect();
}

void ARTSPlayerController::SimpleSelect()
{
	TArray<ARTSUnit*> SelectedUnits;
	//GLog->Log(TEXT("ARTSPlayerController::SimpleSelect()"));
}

void ARTSPlayerController::DragSelect()
{
	TArray<ARTSUnit*> SelectedUnits;
	//GLog->Log(TEXT("ARTSPlayerController::DragSelect()"));
}

void ARTSPlayerController::BeginPlay()
{
	Super::BeginPlay();
	// Setup InputMode
	FInputModeGameAndUI InputModeGameAndUI;
	InputModeGameAndUI.SetHideCursorDuringCapture(false);
	InputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	SetInputMode(InputModeGameAndUI);
}

void ARTSPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ARTSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// if (InputComponent == nullptr)
	// {
	// 	InputComponent = NewObject<UInputComponent>(this,"InputComponent");
	// 	InputComponent->RegisterComponent();
	// }
	InputComponent->BindAction(TEXT("LeftMouseClick"), EInputEvent::IE_Pressed, this, &ARTSPlayerController::ActionInputMousePressed);
	InputComponent->BindAction(TEXT("LeftMouseClick"), EInputEvent::IE_Released, this, &ARTSPlayerController::ActionInputMouseReleased);
}

FVector ARTSPlayerController::GetCursorWorldPlacement(const float Distance)
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

