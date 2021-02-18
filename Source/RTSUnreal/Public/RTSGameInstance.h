// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RTSGameInstance.generated.h"


class AFogOfWar;

/**
 * 
 */
UCLASS()
class RTSUNREAL_API URTSGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	AFogOfWar* GetFogOfWar();
	void SetFogOfWar(AFogOfWar* InFogOfWar);
private:

	UPROPERTY()
	AFogOfWar* FogOfWar = nullptr; 
};
