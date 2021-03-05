// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "RTSWorldBoundsVolume.generated.h"

/**
 * 
 */
UCLASS()
class RTSUNREAL_API ARTSWorldBoundsVolume : public AVolume
{
	GENERATED_BODY()
	
public:
	virtual void PreInitializeComponents() override;

	
	void InitializeWorldBoundsInfo();


	//float GetCellExtentSize();
	int32 GetFogOfWarTextureResolution() const
	{
		return FogOfWarTextureResolution;
	}

	//float GetFogOfWarResolution();
	
	// cell size in unreal unit(cm).
	UPROPERTY(EditDefaultsOnly, Category="RTS")
	float CellExtentSize = 25.f;

	// fog of war texture resolution 
	int32 FogOfWarTextureResolution = 256;

	// fog of war resolution 
	FIntVector FogOfWarResolution;
	
};
