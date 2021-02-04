// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "War3PlayerController.generated.h"

class AWar3Unit;
/**
 * 
 */
UCLASS()
class WAR3UNREAL_API AWar3PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AWar3PlayerController();

	UFUNCTION()
    void ActionInputMousePressed();
	UFUNCTION()
    void ActionInputMouseReleased();

	UFUNCTION()
	void SimpleSelect();
	UFUNCTION()
	void DragSelect();
	
	TArray<AWar3Unit*> CurrentSelectedUints;

	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void SetupInputComponent() override;
	
private:
	UFUNCTION(BlueprintPure, Category="War3PlayerController")
	FVector GetCursorWorldPlacement(const float Distance = 10000.f);
	
	friend class AWar3HUD;
	bool bIsMouseClicked = false;
	FVector2D MouseClickedPos;
	FVector2D MouseHoldingPos;
	
};
