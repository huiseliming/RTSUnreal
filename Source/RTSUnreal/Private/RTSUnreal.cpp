// Fill out your copyright notice in the Description page of Project Settings.

#include "RTSUnreal.h"

#include "FogOfWar/FogOfWarSettings.h"


#define LOCTEXT_NAMESPACE "FRTSUnrealModule"


void FRTSUnrealModule::StartupModule()
{
	FogOfWarSettings = NewObject<UFogOfWarSettings>(GetTransientPackage(), "FogOfWarSettings");
	FogOfWarSettings->AddToRoot();
	
	FogOfWarManagerDelegateHandles.Add(
		FWorldDelegates::OnPostWorldCleanup.AddLambda(
			[this](UWorld* World, bool bSessionEnded, bool bCleanupResources)
			{
			    FogOfWarManagerMap.Remove(World);
			    UE_LOG(LogRTS, Log, TEXT("[%s] FogOfWarManager is removed for: %s"), *UE__FUNC__LINE__, *World->GetName());
			}));
	
	FogOfWarManagerDelegateHandles.Add(
		FWorldDelegates::OnPostWorldInitialization.AddLambda(
		[this](UWorld* World, const UWorld::InitializationValues IVS)
		{
			// Passing an UWorld pointer as Outer in NewObject() and a flag RF_Standalone - is enough to keep your UObject alive during gameplay and auto destruction on game end.
			UFogOfWarManager* FogOfWarManager = NewObject<UFogOfWarManager>(World, *(World->GetName() + TEXT("FogOfWarManager")), RF_Standalone);
	        FogOfWarManagerMap.Add(World, FogOfWarManager);
	        UE_LOG(LogRTS, Log, TEXT("[%s] FogOfWarManager is created for: %s"), *UE__FUNC__LINE__, *World->GetName());
		}));
	
	UE_LOG(LogRTS, Log, TEXT("RTSUnrealModule Loaded"));
}

void FRTSUnrealModule::ShutdownModule()
{
	for(auto& DelegateHandle: FogOfWarManagerDelegateHandles)
		DelegateHandle.Reset();
	FogOfWarManagerMap.Empty();
	FogOfWarSettings->RemoveFromRoot();
	UE_LOG(LogRTS, Log, TEXT("RTSUnrealModule Unload"));
}

UFogOfWarSettings* FRTSUnrealModule::GetFogOfWarSettings() const
{
	check(FogOfWarSettings)
	return FogOfWarSettings;
}

UFogOfWarManager* FRTSUnrealModule::GetFogOfWarManager(UWorld* World) const
{
	return FogOfWarManagerMap.FindRef(World);
}

#undef LOCTEXT_NAMESPACE

#ifdef RTSUNREAL_AS_PRIMARY_GAME_MODULE // As PrimaryGameModule 
IMPLEMENT_PRIMARY_GAME_MODULE( FRTSUnrealModule, RTSUnreal, "RTSUnreal" );
#else
IMPLEMENT_MODULE(FRTSUnrealModule, RTSUnreal)
#endif


DEFINE_LOG_CATEGORY(LogRTS);
