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
	UPROPERTY()
	class AWar3CameraPawn* War3CameraPawn = nullptr;

	
	UPROPERTY(EditAnywhere, Category="AWar3PlayerController")
	float EdgeMoveWidthMultiplier = 10.f;
};
