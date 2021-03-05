// Fill out your copyright notice in the Description page of Project Settings.


#include "FogOfWar/FogOfWarInfo.h"

#include "RTSUnreal.h"
#include "FogOfWar/FogOfWarManager.h"

AFogOfWarInfo::AFogOfWarInfo(const FObjectInitializer& ObjectInitializer)
{
	IFogOfWarDissolveStrategy::GetFogOfWarDissolveStrategies(DissolveStrategies);
}

void AFogOfWarInfo::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	FogOfWarManager = UFogOfWarManager::Get(this,EGetWorldErrorMode::LogAndReturnNull);
	if(!FogOfWarManager)
	{
		UE_LOG(LogRTS, Fatal, TEXT("[%s] Can't get FogOfWarManager in current World"), *UE__FUNC__LINE__);
	}
	RegisterToFogOfWarManager();
}

void AFogOfWarInfo::Destroyed()
{
	DeregisterFromFogOfWarManager();
	Super::Destroyed();
}

void AFogOfWarInfo::RegisterToFogOfWarManager()
{
	FogOfWarManager->RegisterFogOfWarInfo(this);
}

void AFogOfWarInfo::DeregisterFromFogOfWarManager()
{
	FogOfWarManager->DeregisterFogOfWarInfo(this);
	FogOfWarManager = nullptr;
	Cleanup();
}

void AFogOfWarInfo::Initialize()
{
	
}

void AFogOfWarInfo::Cleanup()
{
	
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