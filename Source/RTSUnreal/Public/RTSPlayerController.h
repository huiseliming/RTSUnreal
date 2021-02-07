// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTSPlayerController.generated.h"

class ARTSUnit;
/**
 * 
 */
UCLASS()
class RTSUNREAL_API ARTSPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ARTSPlayerController();

	UFUNCTION()
    void ActionInputMousePressed();
	UFUNCTION()
    void ActionInputMouseReleased();

	UFUNCTION()
	void SimpleSelect();
	UFUNCTION()
	void DragSelect();
	
	TArray<ARTSUnit*> CurrentSelectedUints;

	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void SetupInputComponent() override;
	
private:
	UFUNCTION(BlueprintPure, Category="RTSPlayerController")
	FVector GetCursorWorldPlacement(const float Distance = 10000.f);
	
	friend class ARTSHUD;
	bool bIsMouseClicked = false;
	FVector2D MouseClickedPos;
	FVector2D MouseHoldingPos;
	
};
