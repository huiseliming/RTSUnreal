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

void AFogOfWarInfo::AddAgent(UFogOfWarAgentComponent* InAgent)
{
	
}

void AFogOfWarInfo::RemoveAgent(UFogOfWarAgentComponent* InAgent)
{
		
}