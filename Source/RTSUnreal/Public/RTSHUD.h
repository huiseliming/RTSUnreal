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

	virtual void BeginPlay() override;
	
	virtual void DrawHUD() override;
	
private:
	UPROPERTY()
	class ARTSPlayerController* RTSPlayerController = nullptr;
};
