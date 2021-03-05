// Fill out your copyright notice in the Description page of Project Settings.


#include "FogOfWar/FogOfWarInfo.h"

#include "EngineUtils.h"
#include "RTSUnreal.h"
#include "RTSWorldBoundsVolume.h"
#include "FogOfWar/FogOfWarManager.h"

AFogOfWarInfo::AFogOfWarInfo(const FObjectInitializer& ObjectInitializer)
{
	IFogOfWarDissolveStrategy::GetFogOfWarDissolveStrategies(DissolveStrategies);
	FogOfWarTexture = nullptr;
	FogOfWarTextureBuffer = nullptr;
	FogOfWarUpscaleTexture = nullptr;
	FogOfWarUpscaleTextureBuffer = nullptr;

}

void AFogOfWarInfo::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Initialize();
}

void AFogOfWarInfo::Destroyed()
{
	Cleanup();
	Super::Destroyed();
}

void AFogOfWarInfo::Initialize()
{
	Cleanup();
	UFogOfWarManager* FogOfWarManager = UFogOfWarManager::Get(this,EGetWorldErrorMode::LogAndReturnNull);
	if(!FogOfWarManager)
	{
		UE_LOG(LogRTS, Error, TEXT("[%s] Can't get FogOfWarManager in current World"), *UE__FUNC__LINE__);
	}
	FogOfWarManager->RegisterFogOfWarInfo(this);
	
	// Find current RTSWorldBounds  
	for (TActorIterator<ARTSWorldBoundsVolume> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ARTSWorldBoundsVolume* RTSWorldBoundsVolume = *ActorItr;
		WorldBoundsVolumes.Add(RTSWorldBoundsVolume);
	}
	
	// Currently only supports one RTSWorldBoundsVolume
	if(WorldBoundsVolumes.Num() != 1)
	{
		UE_LOG(LogRTS, Error, TEXT("[%s] WorldBoundsVolumes.Num() = %d, Only supports one RTSWorldBoundsVolume"), *UE__FUNC__LINE__, WorldBoundsVolumes.Num());
	}
	
	ARTSWorldBoundsVolume* RTSWorldBoundsVolume = WorldBoundsVolumes[0];
	const int32 FogOfWarTextureResolution = RTSWorldBoundsVolume->GetFogOfWarTextureResolution();
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
	
}

void AFogOfWarInfo::Cleanup()
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
	UFogOfWarManager* FogOfWarManager = UFogOfWarManager::Get(this,EGetWorldErrorMode::LogAndReturnNull);
	if(!FogOfWarManager)
	{
		UE_LOG(LogRTS, Error, TEXT("[%s] Can't get FogOfWarManager in current World"), *UE__FUNC__LINE__);
	}
	FogOfWarManager->DeregisterFogOfWarInfo(this);
}

void AFogOfWarInfo::Tick(float DeltaTime)
{
	
}

void AFogOfWarInfo::AddAgent(UFogOfWarAgentComponent* InAgent)
{
}

void AFogOfWarInfo::RemoveAgent(UFogOfWarAgentComponent* InAgent)
{
}