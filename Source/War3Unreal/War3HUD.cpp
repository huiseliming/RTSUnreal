// Fill out your copyright notice in the Description page of Project Settings.


#include "War3HUD.h"

#include "War3PlayerController.h"

void AWar3HUD::BeginPlay()
{
	Super::BeginPlay();
	War3PlayerController = Cast<AWar3PlayerController>(GetOwningPlayerController());
}

void AWar3HUD::DrawHUD()
{
	Super::DrawHUD();
	//Update selection box
	if (War3PlayerController->bIsMouseClicked && War3PlayerController->GetMousePosition(War3PlayerController->MouseHoldingPos.X, War3PlayerController->MouseHoldingPos.Y))
	{
		const float ScreenX = War3PlayerController->MouseClickedPos.X < War3PlayerController->MouseHoldingPos.X ? War3PlayerController->MouseClickedPos.X : War3PlayerController->MouseHoldingPos.X ;
		const float ScreenY = War3PlayerController->MouseClickedPos.Y < War3PlayerController->MouseHoldingPos.Y ? War3PlayerController->MouseClickedPos.Y : War3PlayerController->MouseHoldingPos.Y ;
		const float Width = FMath::Abs(War3PlayerController->MouseHoldingPos.X - War3PlayerController->MouseClickedPos.X);
		const float Height = FMath::Abs(War3PlayerController->MouseClickedPos.Y - War3PlayerController->MouseHoldingPos.Y);
		//GLog->Log(FString::Printf(TEXT("ScreenX: %f, ScreenY: %f, Width: %f, Height: %f"), ScreenX, ScreenY, Width, Height));
		DrawRect(FLinearColor(0.5,0.5,0.5,0.3), ScreenX, ScreenY, Width, Height);
		DrawLine(ScreenX, ScreenY, ScreenX +Width, ScreenY, FLinearColor::Gray);
		DrawLine(ScreenX +Width, ScreenY,ScreenX + Width, ScreenY + Height, FLinearColor::Gray);
		DrawLine(ScreenX + Width, ScreenY + Height, ScreenX, ScreenY + Height, FLinearColor::Gray);
		DrawLine(ScreenX, ScreenY + Height, ScreenX, ScreenY, FLinearColor::Gray);
	}
}
