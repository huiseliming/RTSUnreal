// Fill out your copyright notice in the Description page of Project Settings.


#include "FogOfWar/RTSWorldTileVolume.h"

#include "RTSUnreal.h"
#include "Components/BrushComponent.h"
#include "FogOfWar/FogOfWar.h"

void ARTSWorldTileVolume::BeginPlay()
{
}

void ARTSWorldTileVolume::Initialize()
{
	UBrushComponent* RTSWorldBrushComponent = GetBrushComponent();
	const FBoxSphereBounds RTSWorldBounds = RTSWorldBrushComponent->CalcBounds(RTSWorldBrushComponent->GetComponentTransform());

	GridTileNumber = FMath::CeilToInt(FMath::Max(RTSWorldBounds.BoxExtent.X,RTSWorldBounds.BoxExtent.Y) / TileWorldSize) * 2;
	GridWorldSize = FVector(GridTileNumber * TileWorldSize, GridTileNumber * TileWorldSize, RTSWorldBounds.BoxExtent.Z);
	
	UE_LOG(LogRTS, Log, TEXT("RTSWorldTileSize: %d"), GridTileNumber);

	// Calculate tile locations.
	TileWorldLocations.SetNum(GridTileNumber * GridTileNumber);

	check(GridTileNumber / 2 * 2 == GridTileNumber);
	const int32 HalfGridTileNumber = GridTileNumber;
	
	for (int32 TileY = 0; TileY < GridTileNumber; ++TileY)
	{
		for (int32 TileX = 0; TileX < GridTileNumber; ++TileX)
		{
			FVector2D WorldPosition = FVector2D(
                GetActorLocation().Y + TileWorldSize * (TileX + 0.5f - HalfGridTileNumber),
                GetActorLocation().Y + TileWorldSize * (TileY + 0.5f - HalfGridTileNumber));
			TileWorldLocations[TileY * GridTileNumber + TileX] = WorldPosition;
		}
	}
	
	// Calculate tile heights.
	TileHeights.SetNum(GridTileNumber * GridTileNumber);
    
	for (int32 Y = 0; Y <= GridTileNumber - 1; ++Y)
	{
		for (int32 X = 0; X <= GridTileNumber - 1; ++X)
		{
			const FVector2D TileLocationWorld2D = TileXYToTileWorldLocation(X, Y);
			const float TileHeightWorld = CalculateWorldHeightAtLocation(TileLocationWorld2D);
			const int32 TileHeightLevel = FMath::FloorToInt(TileHeightWorld / LevelHeight);
			TileHeights[TileXYToTileIndex(X, Y)] = TileHeightLevel;
		}
	}
}

float ARTSWorldTileVolume::CalculateWorldHeightAtLocation(const FVector2D WorldLocation) const
{
	// Cast ray to hit world.
	TArray<FHitResult> HitResults;

	GetWorld()->LineTraceMultiByChannel(HitResults, FVector(WorldLocation.X, WorldLocation.Y, 10000.0f),
        FVector(WorldLocation.X, WorldLocation.Y, -10000.0f), HeightLevelTraceChannel);

	for (auto& HitResult : HitResults)
	{
		if (HitResult.Actor != nullptr)
		{
			return HitResult.Location.Z;
		}
	}
	return 0.0f;
}
