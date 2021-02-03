// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "War3PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class WAR3UNREAL_API AWar3PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AWar3PlayerController();


	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
private:
	UFUNCTION(BlueprintPure, Category="War3PlayerController")
	FVector GetCursorWorldPlacement(float Distance = 10000.f);
};
