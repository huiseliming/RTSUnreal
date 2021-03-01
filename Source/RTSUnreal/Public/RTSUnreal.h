// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "FogOfWar/FogOfWarManager.h"


#define RTSUNREAL_AS_PRIMARY_GAME_MODULE

// Helper for display code file and line 
#define RTS_FUNC (FString(__FUNCTION__))
#define RTS_LINE (FString::FromInt(__LINE__))
#define RTS_FUNC_LINE (RTS_FUNC + "(" + RTS_LINE + ")")





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


	// FogOfWarManager
	UFogOfWarManager* GetFogOfWarManager(UWorld* World) const ;
private:
	// FogOfWarManager exist one in every world
	TMap<UWorld*, UFogOfWarManager*> FogOfWarManagerMap;
	TArray<FDelegateHandle> FogOfWarManagerDelegateHandles;
};

// Module
DECLARE_LOG_CATEGORY_EXTERN(LogRTS, Log, All);

