﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "FogOfWar/FogOfWarManager.h"
#include "RTSUnreal.h"
#include "EngineUtils.h"
#include "RTSWorldBoundsVolume.h"
#include "FogOfWar/FogOfWarInfo.h"

UFogOfWarManager::UFogOfWarManager()
{
	bIsInitialize = false;
	FogOfWarTexture = nullptr;
	FogOfWarTextureBuffer = nullptr;
	FogOfWarUpscaleTexture = nullptr;
	FogOfWarUpscaleTextureBuffer = nullptr;
}

UFogOfWarManager::~UFogOfWarManager()
{
	UFogOfWarManager::Cleanup();
}

UFogOfWarManager* UFogOfWarManager::Get(const UObject* WorldContextObject, EGetWorldErrorMode ErrorMode)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, ErrorMode))
	{
		return FRTSUnrealModule::Get().GetFogOfWarManager(World);
	}
	return nullptr;
}

void UFogOfWarManager::OnWorldBeginPlay()
{
	UFogOfWarManager::Initialize();
}

void UFogOfWarManager::RegisterFogOfWarInfo(AFogOfWarInfo* InFogOfWarInfo)
{
	FogOfWarInfos.AddUnique(InFogOfWarInfo);
	if (bIsInitialize)
		InFogOfWarInfo->Initialize();
	UE_LOG(LogRTS, Log, TEXT("[%s] register to manager: %s"), *UE__FUNC__LINE__, *InFogOfWarInfo->GetName());
}

void UFogOfWarManager::DeregisterFogOfWarInfo(AFogOfWarInfo* InFogOfWarInfo)
{
	int32 RemovedFogOfWarInfosNum = FogOfWarInfos.Remove(InFogOfWarInfo);
	if (RemovedFogOfWarInfosNum == 0)
	{
		UE_LOG(LogRTS, Warning, TEXT("[%s] No cached info found: %s"), *UE__FUNC__LINE__, *InFogOfWarInfo->GetName());
		return;
	}
	UE_LOG(LogRTS, Log, TEXT("[%s] deregister from Manager %s"), *UE__FUNC__LINE__, *InFogOfWarInfo->GetName());
}

ARTSWorldBoundsVolume* UFogOfWarManager::GetWorldBoundsVolume() const 
{
	return WorldBoundsVolume;
}


void UFogOfWarManager::Initialize()
{
	WorldBoundsVolume = nullptr;
	// Find current RTSWorldBounds  
	for (TActorIterator<ARTSWorldBoundsVolume> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		check(WorldBoundsVolume == nullptr && "Discover the second RTSWorldBoundsVolume");
		WorldBoundsVolume = *ActorItr;
	}
	
	const int32 FogOfWarTextureResolution = WorldBoundsVolume->GetFogOfWarTextureResolution();
	FogOfWarResolution = WorldBoundsVolume->GetFogOfWarResolution();
	check(FMath::IsPowerOfTwo(FogOfWarTextureResolution));
	const int32 CachedUpscaleTextureResolution = FogOfWarTextureResolution * 4;
	
	// Create texture buffer and initialize it
	check(!FogOfWarTextureBuffer);
	FogOfWarTextureBuffer = new uint8[FogOfWarTextureResolution * FogOfWarTextureResolution * 4];
	
	FogOfWarTextureBufferSize = FogOfWarTextureResolution * FogOfWarTextureResolution * sizeof(uint8) * 4;
	FMemory::Memset(FogOfWarTextureBuffer, 0x00, FogOfWarTextureBufferSize);
	
	FogOfWarTextureUpdateRegion =  FUpdateTextureRegion2D(0, 0, 0, 0, FogOfWarTextureResolution, FogOfWarTextureResolution);
	FogOfWarTexture = UTexture2D::CreateTransient(FogOfWarTextureResolution,FogOfWarTextureResolution,EPixelFormat::PF_B8G8R8A8);
	FogOfWarTexture->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
	// FogOfWarTexture->SRGB = false;
	// FogOfWarTexture->CompressionSettings = TextureCompressionSettings::TC_Grayscale;
	// FogOfWarTexture->Filter = TextureFilter::TF_Nearest;
	// FogOfWarTexture->AddressX = TextureAddress::TA_Clamp;
	// FogOfWarTexture->AddressY = TextureAddress::TA_Clamp;
	FogOfWarTexture->UpdateResource();
	
	FogOfWarUpscaleTextureBuffer = new uint8[CachedUpscaleTextureResolution * CachedUpscaleTextureResolution * 4];
	FogOfWarUpscaleTextureBufferSize = CachedUpscaleTextureResolution * CachedUpscaleTextureResolution * sizeof(uint8) * 4;
	FMemory::Memset(FogOfWarUpscaleTextureBuffer, 0x00, FogOfWarUpscaleTextureBufferSize);
	FogOfWarTextureUpdateRegion =  FUpdateTextureRegion2D(0, 0, 0, 0, CachedUpscaleTextureResolution, CachedUpscaleTextureResolution);
	FogOfWarUpscaleTexture = UTexture2D::CreateTransient(CachedUpscaleTextureResolution,CachedUpscaleTextureResolution,EPixelFormat::PF_B8G8R8A8);
	FogOfWarUpscaleTexture->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
	FogOfWarUpscaleTexture->UpdateResource();

	for (auto FogOfWarInfo : FogOfWarInfos)
		FogOfWarInfo->Initialize();
	bIsInitialize = true;
}

void UFogOfWarManager::Cleanup()
{
	if(FogOfWarTexture)
	{
		FogOfWarTexture = nullptr;
	}
	if(FogOfWarUpscaleTexture)
	{
		FogOfWarUpscaleTexture = nullptr;
	}
	if(FogOfWarTextureBuffer)
	{
		delete[] FogOfWarTextureBuffer;
		FogOfWarTextureBuffer = nullptr;
	}
	if(FogOfWarUpscaleTextureBuffer)
	{
		delete[] FogOfWarUpscaleTextureBuffer;
		FogOfWarUpscaleTextureBuffer = nullptr;
	}
	FogOfWarInfos.Empty();
	WorldBoundsVolume = nullptr;
}

void UFogOfWarManager::UpdateFogOfWarTexture()
{
}
