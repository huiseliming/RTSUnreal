// Fill out your copyright notice in the Description page of Project Settings.


#include "FogOfWar/FogOfWarManager.h"
#include "RTSUnreal.h"
#include "FogOfWar/FogOfWarInfo.h"

UFogOfWarManager* UFogOfWarManager::Get(const UObject* WorldContextObject, EGetWorldErrorMode ErrorMode)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, ErrorMode))
	{
		return FRTSUnrealModule::Get().GetFogOfWarManager(World);
	}
	return nullptr;
}

void UFogOfWarManager::RegisterFogOfWarInfo(AFogOfWarInfo* InFogOfWarInfo)
{
	FogOfWarInfos.AddUnique(InFogOfWarInfo);
	UE_LOG(LogRTS, Log, TEXT("[%s] register to manager: %s"), *RTS_FUNC_LINE, *InFogOfWarInfo->GetName());
}

void UFogOfWarManager::DeregisterFogOfWarInfo(AFogOfWarInfo* InFogOfWarInfo)
{
	int32 RemovedFogOfWarInfosNum = FogOfWarInfos.Remove(InFogOfWarInfo);
	if (RemovedFogOfWarInfosNum == 0)
	{
		UE_LOG(LogRTS, Warning, TEXT("[%s] No cached info found: %s"), *RTS_FUNC_LINE, *InFogOfWarInfo->GetName());
		return;
	}
	UE_LOG(LogRTS, Log, TEXT("[%s] deregister from Manager %s"), *RTS_FUNC_LINE, *InFogOfWarInfo->GetName());
}
