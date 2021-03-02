// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/Engine.h"
#include "UObject/Object.h"
#include "FogOfWarManager.generated.h"

/**
 * 
 */
UCLASS()
class RTSUNREAL_API UFogOfWarManager : public UObject
{
	GENERATED_BODY()
	
public:
	// Get FogOfWarManager in current world
	static UFogOfWarManager* Get(const UObject* WorldContextObject, EGetWorldErrorMode ErrorMode = EGetWorldErrorMode::Assert);

	
};
