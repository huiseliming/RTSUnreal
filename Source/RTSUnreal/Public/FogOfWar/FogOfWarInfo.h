// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "FogOfWarDissolveStrategy.h"

#include "GameFramework/Info.h"
#include "FogOfWarInfo.generated.h"

class UFogOfWarAgentComponent;
class UFogOfWarManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFogOfWarInfoAgentModifySignature, UFogOfWarAgentComponent* ,InAgent);


USTRUCT()
struct FFogOfWarCell
{
	GENERATED_BODY()
	FFogOfWarCell()
	{
		VisionNum = 0;
	}
	void AddVision(){ VisionNum++;}
	void RemoveVision(){ VisionNum--;}
	int32 VisionNum;
};

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
	virtual void RegisterToFogOfWarManager();
	virtual void DeregisterFromFogOfWarManager();
public:
	virtual void Initialize();
	virtual void Cleanup();

	FIntVector WorldLocationToCellXY(FVector InWorldLocation) const;
	FVector CellXYToCellCenterWorldLocation(FIntVector CellXY) const;
	
	int32 CellXYToCellIndex(FIntVector InCellXY) const;
	FIntVector CellIndexToCellXY(int32 InCellIndex) const;

	int32 WorldLocationToCellIndex(FVector InWorldLocation) const;
	FVector CellIndexToCellCenterWorldLocation(int32 InCellIndex) const;
	
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
	TArray<UFogOfWarAgentComponent*> Agents;

public:
	TArray<FFogOfWarCell> FogOfWarCells;
	
private:
	UPROPERTY()
	UFogOfWarManager* FogOfWarManager;
};
