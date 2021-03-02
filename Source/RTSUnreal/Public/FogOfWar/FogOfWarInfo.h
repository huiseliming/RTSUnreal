// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "FogOfWarInfo.generated.h"



class UFogOfWarAgentComponent;
/**
 * 
 */
UCLASS(Blueprintable,Blueprintable)
class RTSUNREAL_API AFogOfWarInfo : public AInfo
{
	GENERATED_BODY()

public:
	AFogOfWarInfo(const FObjectInitializer& ObjectInitializer);
	
	virtual void PreInitializeComponents() override;
	virtual void Destroyed() override;
protected:
	virtual void Initialize();
	virtual void Cleanup();
	
	// Registered FogOfWar agents
	UPROPERTY(EditAnywhere, Category = "FogOfWarInfo")
	TArray<UFogOfWarAgentComponent*> FogAgents;

};
