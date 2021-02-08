// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RTSHUD.generated.h"

/**
 * 
 */
UCLASS()
class RTSUNREAL_API ARTSHUD : public AHUD
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	
	virtual void DrawHUD() override;


public:

	/* RTS Selection */
	void StartSelectionRectangle(FVector2D MouseStartPos);
	void UpdateSelectionRectangle(FVector2D MouseUpdatePos);
	void FinishSelectionRectangle(FVector2D MouseFinishPos);

	UPROPERTY()
	TArray<AActor* > CurrentSelectionRectangleActors;
	
	bool bIsMouseClicked = false;
	FVector2D SelectionRectangleStart;
	FVector2D SelectionRectangleEnd;
	
private:
	UPROPERTY()
	class ARTSPlayerController* RTSPlayerController = nullptr;


	
};
