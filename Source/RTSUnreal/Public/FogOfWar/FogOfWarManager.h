// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/Engine.h"
#include "UObject/Object.h"
#include "FogOfWarManager.generated.h"

class AFogOfWarInfo;
class ARTSWorldBoundsVolume;

/**
 * 
 */
UCLASS()
class RTSUNREAL_API UFogOfWarManager : public UObject
{
	GENERATED_BODY()
	
public:
	UFogOfWarManager();
	~UFogOfWarManager();
	// Get FogOfWarManager in current world
	static UFogOfWarManager* Get(const UObject* WorldContextObject, EGetWorldErrorMode ErrorMode = EGetWorldErrorMode::Assert);

	void RegisterFogOfWarInfo(AFogOfWarInfo* FogOfWarInfo);
	void DeregisterFogOfWarInfo(AFogOfWarInfo* FogOfWarInfo);
	
	//AFogOfWarInfo* GetFogOfWarInfo(int32 Index,FString Name) const;
	
private:
	UPROPERTY()
	TArray<AFogOfWarInfo*> FogOfWarInfos;
	UPROPERTY()
	TArray<ARTSWorldBoundsVolume*> WorldBoundsVolumes;
	
private:
	virtual void Initialize();
	virtual void Cleanup();
	
	virtual void UpdateFogOfWarTexture();

	bool bIsInitialize;
private:
    // Original texture on CPU
    UPROPERTY()
    UTexture2D* FogOfWarTexture;
    uint8* FogOfWarTextureBuffer;
    uint32 FogOfWarTextureBufferSize;
    FUpdateTextureRegion2D FogOfWarTextureUpdateRegion;
    
    // Upscaled texture on CPU
    UPROPERTY()
    UTexture2D* FogOfWarUpscaleTexture;
    uint8* FogOfWarUpscaleTextureBuffer;
    uint32 FogOfWarUpscaleTextureBufferSize;
    FUpdateTextureRegion2D FogOfWarUpscaleTextureUpdateRegion;
	
public:
	friend class FRTSUnrealModule;
	// Called after all actors that iterate in the world execute BeginPlay
	void OnWorldBeginPlay();
private:
	FDelegateHandle WorldBeginPlayHandle;
};
