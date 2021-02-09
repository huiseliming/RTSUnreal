// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <Actor.h>

#include "GameFramework/HUD.h"
#include "RTSHUD.generated.h"

class ARTSUnit;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRTSHUDSelectedSignature, AActor*, Actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRTSHUDDeselectedSignature, AActor*, Actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRTSHUDHoveredSignature, AActor*, Actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRTSHUDUnhoveredSignature, AActor*, Actor);

/**
 * 
 */
UCLASS()
class RTSUNREAL_API ARTSHUD : public AHUD
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual  void Tick(float DeltaSeconds) override;
	
	virtual void DrawHUD() override;


	// RTS SelectionRectangle update every DrawHUD call Flag
	bool bSelectionUpdate = false;
	// RTS SelectionRectangle update CurrentSelectionRectangleActors every DrawHUD call Flag
	bool bSelectionFinish = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RTS|Selection")
	bool bUpdateSelectedActorsEveryDrawHUD = true;
	
public:
	// SingleSelect
	void SingleSelect();
	// BoxSelect
	void BoxSelect();
	// Start RTS SelectionRectangle 
	void StartSelectionRectangle();
	// Finish RTS SelectionRectangle 
	void FinishSelectionRectangle();
	// Get RTS SelectionRectangle Actors 
	TArray<AActor* >& GetSelectionRectangleActors();


	// Delegates
	UPROPERTY(BlueprintAssignable, Category = "RTS|Selection")
	FRTSHUDSelectedSignature OnRTSSelectionSelected;
	UPROPERTY(BlueprintAssignable, Category = "RTS|Selection")
	FRTSHUDDeselectedSignature OnRTSSelectionDeselected;
	UPROPERTY(BlueprintAssignable, Category = "RTS|Selection")
	FRTSHUDHoveredSignature OnRTSSelectionHovered;
	UPROPERTY(BlueprintAssignable, Category = "RTS|Selection")
	FRTSHUDUnhoveredSignature OnRTSSelectionUnhovered;
	
	// RTS SingleSelect HoveredActor
	// UPROPERTY()
	// AActor* CurrentHoveredActor = nullptr;

	// RTS BoxSelect HoveredActors
	UPROPERTY()
	TArray<AActor*> CurrentHoveredActors;
	
	// RTS SingleSelect SelectedActor
	UPROPERTY()
	AActor* CurrentSelectedActor = nullptr;
	// RTS SingleSelect index of SelectedActor
	UPROPERTY()
	int32 CurrentSelectedActorIndex = -1;
	// RTS BoxSelect selectedActors
	UPROPERTY()
	TArray<AActor*> CurrentSelectedActors;
	
	// RTS SelectionRectangle Start Pos
	FVector2D SelectionRectangleStart;
	// RTS SelectionRectangle End Pos
	FVector2D SelectionRectangleEnd;
	
private:
	UPROPERTY()
	class ARTSPlayerController* RTSPlayerController = nullptr;

};
