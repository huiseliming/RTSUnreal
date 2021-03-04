// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "FogOfWar/FogOfWarManager.h"


#define RTSUNREAL_AS_PRIMARY_GAME_MODULE

// Helper for display code file and line 
#define UE__FUNCTION__ (FString(__FUNCTION__))
#define UE__LINE__ (FString::FromInt(__LINE__))
#define UE__FUNC__LINE__ (UE__FUNCTION__ + "(" + UE__LINE__ + ")")

class UFogOfWarSettings;

// Module
#ifdef RTSUNREAL_AS_PRIMARY_GAME_MODULE // As PrimaryGameModule 
class FRTSUnrealModule : public FDefaultGameModuleImpl
#else
class FRTSUnrealModule : public IModuleInterface
#endif
{
public:
	
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	
	virtual bool IsGameModule() const override
	{
		return true;
	}

	static FRTSUnrealModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FRTSUnrealModule>("RTSUnreal");
	}

	static bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("RTSUnreal");
	}
	
	UFogOfWarSettings* GetFogOfWarSettings() const;
	
	// FogOfWarManager
	UFogOfWarManager* GetFogOfWarManager(UWorld* World) const ;
private:
	
	UFogOfWarSettings* FogOfWarSettings;
	
	// FogOfWarManager exist one in every world
	TMap<UWorld*, UFogOfWarManager*> FogOfWarManagerMap;
	TArray<FDelegateHandle> FogOfWarManagerDelegateHandles;
};

// Module
DECLARE_LOG_CATEGORY_EXTERN(LogRTS, Log, All);

