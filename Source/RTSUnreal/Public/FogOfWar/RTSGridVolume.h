// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RTSCollisionChannel.h"
#include "GameFramework/Volume.h"
#include "RTSGridVolume.generated.h"


/**
 * 
 */
UCLASS()
class RTSUNREAL_API ARTSGridVolume : public AVolume
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	// Set reasonable default values.
	
public:
	
	FIntVector WorldLocationToGridXYZ(FVector InWorldLocation)
	{
		FVector WorldLocation(InWorldLocation.X,InWorldLocation.Y,0.f);
		FVector GridLocation = WorldLocation - (GetActorLocation() - FVector(GridRowNumber / 2 * GridUnitSize));
		int32 X = FMath::Floor(GridLocation.X / GridUnitSize);
		int32 Y = FMath::Floor(GridLocation.Y / GridUnitSize);
		return FIntVector(X,Y,0);
	}
	
	int32 WorldLocationToTileIndex(FVector InWorldLocation)
	{
		FIntVector GridXYZ = WorldLocationToGridXYZ(InWorldLocation);
		return GridXYZ.X + GridRowNumber * GridXYZ.Y;
	}
	
	FVector2D GridXYToWorldLocation(int32 GridX, int32 GridY) { return GridWorldLocations[GridXYToIndex(GridX, GridY)]; }
	
	int32 GridXYToIndex(int32 GridX, int32 GridY) const { return GridX + GridY * GridRowNumber; }

	FIntVector GetGridNumber() { return FIntVector(GridRowNumber, GridRowNumber, 0); }

	FVector GetWorldGridSize() { return WorldGridSize; }
	
	// Default map height
	UPROPERTY(EditAnywhere, Category = "RTS")
	float DefaultHeight = 0.f;

	// Height of a height level
	UPROPERTY(EditAnywhere, Category = "RTS", meta = (ClampMin = 0))
	float DefaultHeightLevel = 100.f;
	
	// Size of a single tile.
	UPROPERTY(EditAnywhere, Category="RTS")
	float GridUnitSize = 50.f;

	// Default map height
	float MaxHeight = 0.f;
	
	// Default map height
	float MinHeight = 0.f;
	
	// Row and Column of the grid map tile.
	int32 GridRowNumber;
	
	// Size of the Grid.
	FVector WorldGridSize;
	
	//  Cached locations of all grid tiles.
	TArray<FVector2D> GridWorldLocations;
	
	//  Cached height of all grid tiles.
	TArray<int32> TileHeights;
	
	// Collision channel to trace for when determining tile heights.
	TEnumAsByte<ECollisionChannel> HeightLevelCheckTraceChannel = ECC_RTSHeightLevelCheck;


	void Initialize();
	
	float CalculateWorldHeightAtLocation(const FVector2D WorldLocation) const;
};
