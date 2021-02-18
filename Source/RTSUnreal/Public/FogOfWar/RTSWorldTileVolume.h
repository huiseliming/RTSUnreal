// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RTSCollisionChannel.h"
#include "GameFramework/Volume.h"
#include "RTSWorldTileVolume.generated.h"


/**
 * 
 */
UCLASS()
class RTSUNREAL_API ARTSWorldTileVolume : public AVolume
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	// Set reasonable default values.
	
public:
	void Initialize();

	int32 WorldLocationToTileIndex(float InWorldLocationX, float InWorldLocationY)
	{
		FVector WorldLocation(InWorldLocationX,InWorldLocationY,0.f);
		FVector RTSWorldOriToWorldLocation = WorldLocation - (GetActorLocation() - FVector(GridTileNumber / 2 * TileWorldSize));
		int32 X = FMath::Floor(RTSWorldOriToWorldLocation.X / TileWorldSize);
		int32 Y = FMath::Floor(RTSWorldOriToWorldLocation.Y / TileWorldSize);
		return Y * GridTileNumber + X;
	}
	
	FVector2D TileXYToTileWorldLocation(int32 TileX, int32 TileY)
	{
		return TileWorldLocations[TileXYToTileIndex(TileX, TileY)];
	}
	
	int32 TileXYToTileIndex(int32 TileX, int32 TileY) const 
	{
		return TileX + TileY * GridTileNumber;
	}

	float CalculateWorldHeightAtLocation(const FVector2D WorldLocation) const;
	
	// Default map height
	UPROPERTY(EditAnywhere, Category = "RTS")
	float DefaultHeight = 300;

	// Height of a height level
	UPROPERTY(EditAnywhere, Category = "RTS", meta = (ClampMin = 0))
	float LevelHeight = 100;
	
	// Size of a single tile.
	UPROPERTY(EditAnywhere, Category="RTS")
	float TileWorldSize = 50.f;

	// Width and height of the grid map tile.
	int32 GridTileNumber;
	
	// Size of the volume.
	FVector GridWorldSize;
	
	//  Cached locations of all grid tiles.
	TArray<FVector2D> TileWorldLocations;
	
	//  Cached height of all grid tiles.
	TArray<float> TileHeights;
	
	// Collision channel to trace for when determining tile heights.
	TEnumAsByte<ECollisionChannel> HeightLevelTraceChannel = ECC_RTSWorldTileCheck;
};
