// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "RTSGameState.generated.h"

/**
 * 
 */
UCLASS()
class RTSUNREAL_API ARTSGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	ARTSGameState();
protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintPure, Category="RTSGameState")
	void GetGameTime(float& GameTime, int32& Day, int32& Hour, int32& Minute, int32& Second);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RTSGameState")
	float GameSpeed = 1.0f;
	UPROPERTY(BlueprintReadOnly, Category="RTSGameState")
	float GameTimeSeconds = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category="RTSGameState")
	int GameDay = 0;
};
