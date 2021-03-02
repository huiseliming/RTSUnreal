// Fill out your copyright notice in the Description page of Project Settings.


#include "FogOfWar/FogOfWarInfo.h"
#include "RTSUnreal.h"
#include "FogOfWar/FogOfWarManager.h"

AFogOfWarInfo::AFogOfWarInfo(const FObjectInitializer& ObjectInitializer)
{
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
		UE_LOG(LogRTS, Error, TEXT("[%s] Can't get FogOfWarManager in current World"), *RTS_FUNC_LINE);
	}
	FogOfWarManager->RegisterFogOfWarInfo(this);
}

void AFogOfWarInfo::Cleanup()
{
	UFogOfWarManager* FogOfWarManager = UFogOfWarManager::Get(this,EGetWorldErrorMode::LogAndReturnNull);
	if(!FogOfWarManager)
	{
		UE_LOG(LogRTS, Error, TEXT("[%s] Can't get FogOfWarManager in current World"), *RTS_FUNC_LINE);
	}
	FogOfWarManager->DeregisterFogOfWarInfo(this);
}
