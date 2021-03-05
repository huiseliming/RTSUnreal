// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FogOfWarDissolveStrategy.h"

#include "GameFramework/Info.h"
#include "FogOfWarInfo.generated.h"

class UFogOfWarAgentComponent;
class ARTSWorldBoundsVolume;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFogOfWarInfoAgentModifySignature, UFogOfWarAgentComponent* ,InAgent);

/**
 * 
 */
UCLASS(Blueprintable,Blueprintable)
class RTSUNREAL_API AFogOfWarInfo : public AInfo
{
	GENERATED_BODY()

public:
	AFogOfWarInfo(const FObjectInitializer& ObjectInitializer);
	
	virtual void PostInitializeComponents() override;
	virtual void Destroyed() override;
protected:
	virtual void Initialize();
	virtual void Cleanup();
	
public:
	virtual void Tick(float DeltaTime) override;

public:
	void AddAgent(UFogOfWarAgentComponent* InAgent);
	void RemoveAgent(UFogOfWarAgentComponent* InAgent);
	
	FFogOfWarInfoAgentModifySignature OnAddAgent;
	FFogOfWarInfoAgentModifySignature OnRemoveAgent;
	

	TArray<IFogOfWarDissolveStrategy> DissolveStrategies;
	
	// Registered FogOfWar agents
	UPROPERTY(EditAnywhere, Category = "FogOfWarInfo")
	TArray<UFogOfWarAgentComponent*> FogAgents;
	UPROPERTY()
	TArray<ARTSWorldBoundsVolume*> WorldBoundsVolumes;

	// Original texture on CPU
	UPROPERTY()
	UTexture2D* FogOfWarTexture;
	uint8* FogOfWarTextureBuffer;
	uint32 FogOfWarTextureBufferSize;
	FUpdateTextureRegion2D FogOfWarTextureUpdateRegion;
	
	// Upscaled texture on CPU
	UPROPERTY()
	UTexture2D* FogOfWarUpscaleTexture;
	uint8* FogOfWarUpscaleTextureBuffer;
	uint32 FogOfWarUpscaleTextureBufferSize;
	FUpdateTextureRegion2D FogOfWarUpscaleTextureUpdateRegion;
};
