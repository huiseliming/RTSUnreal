// Fill out your copyright notice in the Description page of Project Settings.


#include "FogOfWar/RTSGridVolume.h"

#include "RTSUnreal.h"
#include "Components/BrushComponent.h"
#include "FogOfWar/FogOfWar.h"

void ARTSGridVolume::BeginPlay()
{
}

void ARTSGridVolume::Initialize()
{
	UBrushComponent* RTSWorldBrushComponent = GetBrushComponent();
	const FBoxSphereBounds RTSWorldBounds = RTSWorldBrushComponent->CalcBounds(RTSWorldBrushComponent->GetComponentTransform());


	// Calculate GridRowNumber and WorldGridSize
	GridRowNumber = FMath::CeilToInt(FMath::Max(RTSWorldBounds.BoxExtent.X,RTSWorldBounds.BoxExtent.Y) / GridUnitSize) * 2;
	WorldGridSize = FVector(GridRowNumber * GridRowNumber, GridRowNumber * GridRowNumber,0);
	MaxHeight = GetActorLocation().Z + RTSWorldBounds.BoxExtent.Z;
	MinHeight = GetActorLocation().Z - RTSWorldBounds.BoxExtent.Z;
	UE_LOG(LogRTS, Log, TEXT("GridRowNumber: %d"), GridRowNumber);
	UE_LOG(LogRTS, Log, TEXT("WorldGridSize: %s"), *WorldGridSize.ToString());
	
	GridWorldLocations.SetNum(GridRowNumber * GridRowNumber);
	TileHeights.SetNum(GridRowNumber * GridRowNumber);

	check(GridRowNumber / 2 * 2 == GridRowNumber && "GridRowNumber must multiples of 2");
	const int32 HalfGridRowNumber = GridRowNumber / 2;
	// Calculate grid locations.
	for (int32 TileY = 0; TileY < GridRowNumber; ++TileY)
	{
		for (int32 TileX = 0; TileX < GridRowNumber; ++TileX)
		{
			const FVector2D WorldPosition = FVector2D(
                GetActorLocation().X + GridUnitSize * (TileX + 0.5f - HalfGridRowNumber),
                GetActorLocation().Y + GridUnitSize * (TileY + 0.5f - HalfGridRowNumber));
			GridWorldLocations[TileX + TileY * GridRowNumber] = WorldPosition;
		}
	}
	
	// Calculate tile heights.
	for (int32 Y = 0; Y <= GridRowNumber - 1; ++Y)
	{
		for (int32 X = 0; X <= GridRowNumber - 1; ++X)
		{
			const FVector2D GridWorldLocation2D = GridXYToWorldLocation(X, Y);
			const float TileHeightWorld = CalculateWorldHeightAtLocation(GridWorldLocation2D);
			const int32 TileHeightLevel = FMath::FloorToInt(TileHeightWorld / DefaultHeightLevel);
			TileHeights[GridXYToIndex(X, Y)] = TileHeightLevel;
		}
	}
}

float ARTSGridVolume::CalculateWorldHeightAtLocation(const FVector2D WorldLocation) const
{
	// Cast ray to hit world.
	TArray<FHitResult> HitResults;

	GetWorld()->LineTraceMultiByChannel(HitResults, FVector(WorldLocation.X, WorldLocation.Y, MaxHeight),
        FVector(WorldLocation.X, WorldLocation.Y, MinHeight), HeightLevelCheckTraceChannel);

	for (auto& HitResult : HitResults)
	{
		if (HitResult.Actor != nullptr)
		{
			return HitResult.Location.Z;
		}
	}
	return 0.0f;
}
