// Fill out your copyright notice in the Description page of Project Settings.


#include "FogOfWar/FogOfWarDissolveStrategy.h"

// Add default functionality here for any IFogOfWarRadiusDissolveStrategy functions that are not pure virtual.
IFogOfWarDissolveStrategy::~IFogOfWarDissolveStrategy() = default;

void IFogOfWarDissolveStrategy::GetFogOfWarDissolveStrategies(TArray<IFogOfWarDissolveStrategy>& DissolveStrategies)
{
	DissolveStrategies.Emplace(FFogOfWarCircleDissolveStrategy()); // EFogOfWarDissolveStrategy::Circle
	DissolveStrategies.Emplace(FFogOfWarSquareDissolveStrategy()); // EFogOfWarDissolveStrategy::Square
}

bool FFogOfWarCircleDissolveStrategy::IsInRadius(int32 CenterX, int32 CenterY, int32 Radius, int32 X, int32 Y)
{
	const int32 XSquare = FMath::Square(X - CenterX);
	const int32 YSquare = FMath::Square(Y - CenterY);
	return XSquare + YSquare < FMath::Square(Radius);
}

bool FFogOfWarSquareDissolveStrategy::IsInRadius(int32 CenterX, int32 CenterY, int32 Radius, int32 X, int32 Y)
{
	return (FMath::Abs(X - CenterX) < Radius && FMath::Abs(Y - CenterY) < Radius);
}
