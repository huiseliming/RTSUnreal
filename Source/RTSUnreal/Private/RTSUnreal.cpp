// Fill out your copyright notice in the Description page of Project Settings.

#include "RTSUnreal.h"

#define LOCTEXT_NAMESPACE "FRTSUnrealModule"

void FRTSUnrealModule::StartupModule()
{
	FWorldDelegates::OnPostWorldCleanup.AddLambda([this](UWorld* World, bool bSessionEnded, bool bCleanupResources) {
		auto FogOfWarManager = FogOfWarManagerMap.FindRef(World);
		FogOfWarManager->RemoveFromRoot();
	    FogOfWarManagerMap.Remove(World);
	    UE_LOG(LogRTS, Log, TEXT("[%s] Fog Controller is removed for: %s"), *RTS_FUNC_LINE, *World->GetName());
	});
	
	FWorldDelegates::OnPostWorldInitialization.AddLambda([this](UWorld* World, const UWorld::InitializationValues IVS) {
        auto FogController = NewObject<UFogOfWarManager>(GetTransientPackage());
        FogController->SetFlags(RF_Standalone);
        FogController->AddToRoot();

        FogOfWarManagerMap.Add(World, FogController);

        UE_LOG(LogRTS, Log, TEXT("[%s] Fog Controller is created for: %s"), *RTS_FUNC_LINE, *World->GetName());
    });
	
	UE_LOG(LogRTS, Log, TEXT("RTSUnrealModule Loaded"));
}

void FRTSUnrealModule::ShutdownModule()
{
	UE_LOG(LogRTS, Log, TEXT("RTSUnrealModule Unload"));

	for(auto& DelegateHandle: FogOfWarManagerDelegateHandles)
		DelegateHandle.Reset();
	
	for (auto FogOfWarManager : FogOfWarManagerMap)
	{
		FogOfWarManager.Value->RemoveFromRoot();
	}
	FogOfWarManagerMap.Empty();
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
