// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSHUD.h"

#include "RTSPlayerController.h"

void ARTSHUD::BeginPlay()
{
	Super::BeginPlay();
	RTSPlayerController = Cast<ARTSPlayerController>(GetOwningPlayerController());
}

void ARTSHUD::DrawHUD()
{
	Super::DrawHUD();
	//Update selection box
	if (RTSPlayerController->bIsMouseClicked && RTSPlayerController->GetMousePosition(SelectionRectangleEnd.X, SelectionRectangleEnd.Y))
	{
		const float ScreenX = SelectionRectangleStart.X < SelectionRectangleEnd.X ? SelectionRectangleStart.X : SelectionRectangleEnd.X ;
		const float ScreenY = SelectionRectangleStart.Y < SelectionRectangleEnd.Y ? SelectionRectangleStart.Y : SelectionRectangleEnd.Y ;
		const float Width = FMath::Abs(SelectionRectangleEnd.X - SelectionRectangleStart.X);
		const float Height = FMath::Abs(SelectionRectangleStart.Y - SelectionRectangleEnd.Y);
		//GLog->Log(FString::Printf(TEXT("ScreenX: %f, ScreenY: %f, Width: %f, Height: %f"), ScreenX, ScreenY, Width, Height));
		DrawRect(FLinearColor(0.5,0.5,0.5,0.3), ScreenX, ScreenY, Width, Height);
		DrawLine(ScreenX, ScreenY, ScreenX +Width, ScreenY, FLinearColor::Gray);
		DrawLine(ScreenX +Width, ScreenY,ScreenX + Width, ScreenY + Height, FLinearColor::Gray);
		DrawLine(ScreenX + Width, ScreenY + Height, ScreenX, ScreenY + Height, FLinearColor::Gray);
		DrawLine(ScreenX, ScreenY + Height, ScreenX, ScreenY, FLinearColor::Gray);
		GetActorsInSelectionRectangle(AActor::StaticClass(), SelectionRectangleStart, SelectionRectangleEnd,CurrentSelectionRectangleActors);
	}
}