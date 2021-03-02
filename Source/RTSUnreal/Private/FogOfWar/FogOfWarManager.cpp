// Fill out your copyright notice in the Description page of Project Settings.


#include "FogOfWar/FogOfWarManager.h"
#include "RTSUnreal.h"

UFogOfWarManager* UFogOfWarManager::Get(const UObject* WorldContextObject, EGetWorldErrorMode ErrorMode)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, ErrorMode))
	{
		return FRTSUnrealModule::Get().GetFogOfWarManager(World);
	}
	return nullptr;
}
