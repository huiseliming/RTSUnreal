// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "RTSSelectionComponent.h"
#include "Engine/Selection.h"
#include "GameFramework/PlayerController.h"
#include "RTSPlayerController.generated.h"

class ARTSUnit;
class ARTSCameraPawn;
class ARTSHUD;

/**
 * 
 */
UCLASS()
class RTSUNREAL_API ARTSPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ARTSPlayerController();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="RTSCameraPawn", meta=(AllowPrivateAccess = "true"))
	URTSSelectionComponent* RTSSelectionComponent = nullptr;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void SetupInputComponent() override;

public:
	/* Select Start */
	UFUNCTION()
    void ActionInputSelectStart();
	UFUNCTION()
    void ActionInputSelectFinish();
	
private:
	
	UFUNCTION(BlueprintPure, Category="RTSPlayerController")
    FVector GetCursorWorldPlacement(const float Distance = 10000.f);
	
	UPROPERTY()
	ARTSHUD* RTSHUD = nullptr;
};
