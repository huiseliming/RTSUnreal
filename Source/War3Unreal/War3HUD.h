// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "War3HUD.generated.h"

/**
 * 
 */
UCLASS()
class WAR3UNREAL_API AWar3HUD : public AHUD
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	
	virtual void DrawHUD() override;
	
private:
	UPROPERTY()
	class AWar3PlayerController* War3PlayerController = nullptr;
};
