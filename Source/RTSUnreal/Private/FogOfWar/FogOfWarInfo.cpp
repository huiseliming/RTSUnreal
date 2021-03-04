// Fill out your copyright notice in the Description page of Project Settings.


#include "FogOfWar/FogOfWarInfo.h"
#include "RTSUnreal.h"
#include "FogOfWar/FogOfWarManager.h"

AFogOfWarInfo::AFogOfWarInfo(const FObjectInitializer& ObjectInitializer)
{
	IFogOfWarDissolveStrategy::GetFogOfWarDissolveStrategies(DissolveStrategies);
}

void AFogOfWarInfo::PreInitializeComponents()
{
	Initialize();
	Super::PreInitializeComponents();
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

	
	// // Cache texture size values
	// int32 CachedTextureResolution = FVaFogOfWarModule::Get().GetSettings()->FogLayerResolution;
	// check(FMath::IsPowerOfTwo(CachedTextureResolution));
	// int32 CachedUpscaleResolution = CachedTextureResolution * 4;
	//
	// // Create texture buffer and initialize it
	// check(!SourceBuffer);
	// SourceW = CachedTextureResolution;
	// SourceH = CachedTextureResolution;
	// SourceBuffer = new uint8[SourceW * SourceH];
	// SourceBufferLength = SourceW * SourceH * sizeof(uint8);
	// FMemory::Memset(SourceBuffer, ZeroBufferValue, SourceBufferLength);
	//
	// if (bUseUpscaleBuffer)
	// {
	// 	// Create texture buffer for upscaled texture and initialize it
	// 	check(!UpscaleBuffer);
	// 	UpscaleW = CachedUpscaleResolution;
	// 	UpscaleH = CachedUpscaleResolution;
	// 	UpscaleBuffer = new uint8[UpscaleW * UpscaleH];
	// 	UpscaleBufferLength = UpscaleW * UpscaleH * sizeof(uint8);
	// 	FMemory::Memset(UpscaleBuffer, ZeroBufferValue, UpscaleBufferLength);
	// }
	//
	// // Prepare debug textures if required
	// if (bDebugBuffers)
	// {
	// 	SourceUpdateRegion = FUpdateTextureRegion2D(0, 0, 0, 0, SourceW, SourceH);
	// 	SourceTexture = UTexture2D::CreateTransient(SourceW, SourceH, EPixelFormat::PF_G8);
	// 	SourceTexture->CompressionSettings = TextureCompressionSettings::TC_Grayscale;
	// 	SourceTexture->SRGB = false;
	// 	SourceTexture->Filter = TextureFilter::TF_Nearest;
	// 	SourceTexture->AddressX = TextureAddress::TA_Clamp;
	// 	SourceTexture->AddressY = TextureAddress::TA_Clamp;
	// 	SourceTexture->UpdateResource();
	// }
	//
	// if (bUseUpscaleBuffer)
	// {
	// 	// Upscale texture is the one we export to user
	// 	UpscaleUpdateRegion = FUpdateTextureRegion2D(0, 0, 0, 0, UpscaleW, UpscaleH);
	// 	UpscaleTexture = UTexture2D::CreateTransient(UpscaleW, UpscaleH, EPixelFormat::PF_G8);
	// 	UpscaleTexture->CompressionSettings = TextureCompressionSettings::TC_Grayscale;
	// 	UpscaleTexture->SRGB = false;
	// 	UpscaleTexture->Filter = TextureFilter::TF_Nearest;
	// 	UpscaleTexture->AddressX = TextureAddress::TA_Clamp;
	// 	UpscaleTexture->AddressY = TextureAddress::TA_Clamp;
	// 	UpscaleTexture->UpdateResource();
	// }

	
}

void AFogOfWarInfo::Cleanup()
{
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

void AFogOfWarInfo::UpdateLayer(bool bForceFullUpdate)
{
	
}

void AFogOfWarInfo::AddAgent(UFogOfWarAgentComponent* InAgent)
{
}

void AFogOfWarInfo::RemoveAgent(UFogOfWarAgentComponent* InAgent)
{
}
