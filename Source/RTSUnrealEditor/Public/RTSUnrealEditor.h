// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FRTSUnrealEditorModule : public IModuleInterface
{
public:
	// IModuleInterface implementation
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	
	static FRTSUnrealEditorModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FRTSUnrealEditorModule>(
            "RTSUnrealEditor");
	}
	
	static bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("RTSUnrealEditor");
	}
};



DECLARE_LOG_CATEGORY_EXTERN(LogRTSE, Log, All);
