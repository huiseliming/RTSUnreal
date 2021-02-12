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
	RTSHUD = Cast<ARTSHUD>(GetHUD());
	if (!RTSHUD)
		UE_LOG(LogRTS, Fatal, TEXT("Can't Get RTSHUD From AHUD::GetHUD()"));
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
	InputComponent->BindAction(TEXT("RTSSelect"), EInputEvent::IE_Pressed, this, &ARTSPlayerController::ActionInputSelectStart);
	InputComponent->BindAction(TEXT("RTSSelect"), EInputEvent::IE_Released, this, &ARTSPlayerController::ActionInputSelectFinish);
}

void ARTSPlayerController::ActionInputSelectStart()
{
	RTSHUD->StartSelectionRectangle();
}

void ARTSPlayerController::ActionInputSelectFinish()
{
	RTSHUD->FinishSelectionRectangle();
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
