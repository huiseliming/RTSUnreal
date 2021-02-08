// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSPlayerController.h"
#include "RTSHUD.h"
#include "RTSUnit.h"
#include "RTSUnreal.h"
#include "GameFramework/HUD.h"
#include "Kismet/GameplayStatics.h"

ARTSPlayerController::ARTSPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	RTSSelectionComponent = CreateDefaultSubobject<URTSSelectionComponent>(TEXT("RTSSelection"));
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

	RTSHUD = Cast<ARTSHUD>(GetHUD());
	if (RTSHUD)
		UE_LOG(RTSLog, Warning, TEXT("Can't Get RTSHUD From AHUD::GetHUD()"));
	InputComponent->BindAction(TEXT("LeftMouseClick"), EInputEvent::IE_Pressed, this, &ARTSPlayerController::ActionInputSelectBegin);
	InputComponent->BindAction(TEXT("LeftMouseClick"), EInputEvent::IE_Released, this, &ARTSPlayerController::ActionInputSelectEnd);
}


void ARTSPlayerController::ActionInputSelectBegin()
{
	FVector2D MousePosition;
	if (GetMousePosition(MousePosition.X, MousePosition.Y))
	{
		RTSHUD->StartSelectionRectangle(MousePosition);
		bIsMouseClicked = true;
	}
}

void ARTSPlayerController::ActionInputSelectEnd()
{
	bIsMouseClicked = false;
	if((MouseHoldingPos - MouseClickedPos).Size() > 3.0f)
		RTSSelectionComponent->SelectBox(MouseClickedPos,MouseHoldingPos);
	else
		RTSSelectionComponent->Select();
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
