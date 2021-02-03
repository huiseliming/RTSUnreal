// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "War3GameState.generated.h"

/**
 * 
 */
UCLASS()
class WAR3UNREAL_API AWar3GameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	AWar3GameState();
protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintPure, Category="War3GameState")
	void GetGameTime(float& GameTime, int32& Day, int32& Hour, int32& Minute, int32& Second);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="War3GameState")
	float GameSpeed = 1.0f;
	UPROPERTY(BlueprintReadOnly, Category="War3GameState")
	float GameTimeSeconds = 0.0f;
	UPROPERTY(BlueprintReadOnly, Category="War3GameState")
	int GameDay = 0;
};
