// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FogOfWarDissolveStrategy.generated.h"

UENUM(BlueprintType)
enum class EFogOfWarDissolveStrategy : uint8
{
	Circle = 0,
    Square = 1,
    Max UMETA(Hidden)
};

class RTSUNREAL_API IFogOfWarDissolveStrategy
{
public:
	IFogOfWarDissolveStrategy() = default;
	virtual ~IFogOfWarDissolveStrategy();
	
	static void GetFogOfWarDissolveStrategies(TArray<IFogOfWarDissolveStrategy>& DissolveStrategies);
	
	virtual bool IsInRadius(int32 CenterX, int32 CenterY, int32 Radius, int32 X, int32 Y) { return false; };
};

class RTSUNREAL_API FFogOfWarCircleDissolveStrategy : public IFogOfWarDissolveStrategy
{
public:
	virtual bool IsInRadius(int32 CenterX, int32 CenterY, int32 Radius, int32 X, int32 Y) override;
};

class RTSUNREAL_API FFogOfWarSquareDissolveStrategy : public IFogOfWarDissolveStrategy
{
public:
	virtual bool IsInRadius(int32 CenterX, int32 CenterY, int32 Radius, int32 X, int32 Y) override;
};


