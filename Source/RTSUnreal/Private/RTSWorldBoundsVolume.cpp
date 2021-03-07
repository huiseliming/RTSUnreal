// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSWorldBoundsVolume.h"
#include "RTSUnreal.h"
#include "Components/BrushComponent.h"

// void ARTSWorldBoundsVolume::PostLoad()
// {
// 	Super::PostLoad();
// 	UBrushComponent* RTSWorldBrushComponent = GetBrushComponent();
// 	const FBoxSphereBounds RTSWorldBounds = RTSWorldBrushComponent->CalcBounds(RTSWorldBrushComponent->GetComponentTransform());
//
// 	UE_LOG(LogRTS, Warning, TEXT(" PostLoad O (%f,%f,%f), B(%f,%f,%f)"),
//         RTSWorldBounds.Origin.X,RTSWorldBounds.Origin.Y,RTSWorldBounds.Origin.Z,
//         RTSWorldBounds.BoxExtent.X,RTSWorldBounds.BoxExtent.Y,RTSWorldBounds.BoxExtent.Z);
// }
//
// void ARTSWorldBoundsVolume::PostActorCreated()
// {
// 	Super::PostActorCreated();
// 	UBrushComponent* RTSWorldBrushComponent = GetBrushComponent();
// 	const FBoxSphereBounds RTSWorldBounds = RTSWorldBrushComponent->CalcBounds(RTSWorldBrushComponent->GetComponentTransform());
//
// 	UE_LOG(LogRTS, Warning, TEXT(" PostLoad O (%f,%f,%f), B(%f,%f,%f)"),
//         RTSWorldBounds.Origin.X,RTSWorldBounds.Origin.Y,RTSWorldBounds.Origin.Z,
//         RTSWorldBounds.BoxExtent.X,RTSWorldBounds.BoxExtent.Y,RTSWorldBounds.BoxExtent.Z);
// }

void ARTSWorldBoundsVolume::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	InitializeWorldBoundsInfo();
}

void ARTSWorldBoundsVolume::InitializeWorldBoundsInfo()
{
	UBrushComponent* RTSWorldBoundsBrushComponent = GetBrushComponent();
	const FBoxSphereBounds RTSWorldBounds = RTSWorldBoundsBrushComponent->CalcBounds(RTSWorldBoundsBrushComponent->GetComponentTransform());

	// Calculate GridRowNumber and WorldGridSize
	const int32 MaxOfFogOfWarResolution = FMath::CeilToInt(FMath::Max(RTSWorldBounds.BoxExtent.X,RTSWorldBounds.BoxExtent.Y) / (CellExtentSize * 2)) * 2;
	FogOfWarTextureResolution = FMath::RoundUpToPowerOfTwo(MaxOfFogOfWarResolution);
	if(FogOfWarTextureResolution > 1024 * 4)
	{
		UE_LOG(LogRTS, Error, TEXT("[%s] Can't support FogOfWarResolution greater than 4096"), *UE__FUNC__LINE__);
	}
	else if(FogOfWarTextureResolution > 1024)
	{
		UE_LOG(LogRTS, Warning, TEXT("[%s] FogOfWarResolution is %d greater than 4096"), *UE__FUNC__LINE__, FogOfWarTextureResolution);
	}
	const FVector WorldBoundsLocation = RTSWorldBoundsBrushComponent->GetComponentLocation();
	FogOfWarCoordinateOrigin = FVector(
		WorldBoundsLocation.X - FogOfWarTextureResolution * CellExtentSize,
		WorldBoundsLocation.Y - FogOfWarTextureResolution * CellExtentSize,
		WorldBoundsLocation.Z);
	
	FogOfWarResolution.X = FMath::CeilToInt(RTSWorldBounds.BoxExtent.X / (CellExtentSize * 2)) * 2;
	FogOfWarResolution.Y = FMath::CeilToInt(RTSWorldBounds.BoxExtent.Y / (CellExtentSize * 2)) * 2;
	FogOfWarResolution.Z = 0;
	
	UE_LOG(LogRTS, Log, TEXT("[%s] FogOfWarResolution(%s), FogOfWarTextureResolution(%d) "), *UE__FUNC__LINE__, *FogOfWarResolution.ToString(),FogOfWarTextureResolution);
	
}

FVector ARTSWorldBoundsVolume::GetFogOfWarCoordinateOrigin() const 
{
	return FogOfWarCoordinateOrigin;
}
