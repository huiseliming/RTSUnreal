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
	War3CameraPawn = Cast<AWar3CameraPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	FInputModeGameAndUI InputModeGameAndUI;
	InputModeGameAndUI.SetHideCursorDuringCapture(false);
	InputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	SetInputMode(InputModeGameAndUI);
}

void AWar3PlayerController::Tick(float DeltaSeconds)
{
	int32 ViewportSizeX,ViewportSizeY;
	float MouseLocationX,MouseLocationY;
	GetViewportSize(ViewportSizeX,ViewportSizeY);
	if (ViewportSizeX != 0 && GetMousePosition(MouseLocationX,MouseLocationY))
	{
		GLog->Log(FString::Printf(TEXT("%d, %d, %f, %f"),  ViewportSizeX, ViewportSizeY, MouseLocationX, MouseLocationY));
		const float Viewport1KBase = FMath::Min(ViewportSizeY,ViewportSizeY) / 1080.f;
		const float EdgeMoveWidth = EdgeMoveWidthMultiplier * Viewport1KBase;
		if (MouseLocationX + EdgeMoveWidth >= ViewportSizeX)
		{
			War3CameraPawn->AxisInputMoveRight(	(EdgeMoveWidth - (ViewportSizeX - MouseLocationX)) / EdgeMoveWidth);
		}
		if (MouseLocationX - EdgeMoveWidth <= 0.f)
		{
			War3CameraPawn->AxisInputMoveRight((- EdgeMoveWidth - MouseLocationX) / EdgeMoveWidth);
		}
		if (MouseLocationY + EdgeMoveWidth >= ViewportSizeY)
		{
			War3CameraPawn->AxisInputMoveForward(-(EdgeMoveWidth - (ViewportSizeY - MouseLocationY)) / EdgeMoveWidth);
		}
		if (MouseLocationY - EdgeMoveWidth <= 0.f)
		{
			War3CameraPawn->AxisInputMoveForward((EdgeMoveWidth - MouseLocationY) / EdgeMoveWidth);
		}
	}
}
