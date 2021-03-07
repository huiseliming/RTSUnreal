// Fill out your copyright notice in the Description page of Project Settings.


#include "FogOfWar/FogOfWarInfo.h"

#include "RTSUnreal.h"
#include "RTSWorldBoundsVolume.h"
#include "FogOfWar/FogOfWarManager.h"

AFogOfWarInfo::AFogOfWarInfo(const FObjectInitializer& ObjectInitializer)
{
	IFogOfWarDissolveStrategy::GetFogOfWarDissolveStrategies(DissolveStrategies);
}

void AFogOfWarInfo::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	FogOfWarManager = UFogOfWarManager::Get(this,EGetWorldErrorMode::LogAndReturnNull);
	if(!FogOfWarManager)
	{
		UE_LOG(LogRTS, Fatal, TEXT("[%s] Can't get FogOfWarManager in current World"), *UE__FUNC__LINE__);
	}
	RegisterToFogOfWarManager();
}

void AFogOfWarInfo::Destroyed()
{
	DeregisterFromFogOfWarManager();
	Super::Destroyed();
}

void AFogOfWarInfo::RegisterToFogOfWarManager()
{
	FogOfWarManager->RegisterFogOfWarInfo(this);
}

void AFogOfWarInfo::DeregisterFromFogOfWarManager()
{
	FogOfWarManager->DeregisterFogOfWarInfo(this);
	FogOfWarManager = nullptr;
	Cleanup();
}

void AFogOfWarInfo::Initialize()
{
	const FIntVector FogOfWarResolution = FogOfWarManager->FogOfWarResolution;
	FogOfWarCells.Init(FFogOfWarCell(), FogOfWarResolution.X * FogOfWarResolution.Y);
}

void AFogOfWarInfo::Cleanup()
{
	
}

FIntVector AFogOfWarInfo::WorldLocationToCellXY(FVector InWorldLocation) const
{
	const FVector FogOfWarCoordinateSystemLocation = InWorldLocation - FogOfWarManager->GetWorldBoundsVolume()->GetFogOfWarCoordinateOrigin();
	const float CellSize = FogOfWarManager->GetWorldBoundsVolume()->CellExtentSize;
	const FVector CellXYVector = FogOfWarCoordinateSystemLocation / CellSize * 2;
	return FIntVector(FMath::FloorToInt(CellXYVector.X), FMath::FloorToInt(CellXYVector.Y), 0);
}

FVector AFogOfWarInfo::CellXYToCellCenterWorldLocation(FIntVector CellXY) const
{
	check(false);
	const float CellExtentSize = FogOfWarManager->GetWorldBoundsVolume()->CellExtentSize;
	const float CellSize = FogOfWarManager->GetWorldBoundsVolume()->CellExtentSize;
	return FVector(CellXY.X * CellSize + CellExtentSize, CellXY.Y * CellSize + CellExtentSize, 0) ;
}

int32 AFogOfWarInfo::CellXYToCellIndex(FIntVector InCellXY) const
{
	return InCellXY.X + InCellXY.Y * FogOfWarManager->GetWorldBoundsVolume()->FogOfWarTextureResolution;
}

FIntVector AFogOfWarInfo::CellIndexToCellXY(int32 InCellIndex) const
{
	return FIntVector(InCellIndex % FogOfWarManager->GetWorldBoundsVolume()->FogOfWarTextureResolution,
		InCellIndex / FogOfWarManager->GetWorldBoundsVolume()->FogOfWarTextureResolution,
		0);
}

int32 AFogOfWarInfo::WorldLocationToCellIndex(FVector InWorldLocation) const
{
	return CellXYToCellIndex(WorldLocationToCellXY(InWorldLocation));
}

FVector AFogOfWarInfo::CellIndexToCellCenterWorldLocation(int32 InCellIndex) const
{
	return CellXYToCellCenterWorldLocation(CellIndexToCellXY(InCellIndex));
}

void AFogOfWarInfo::Tick(float DeltaTime)
{
	for (auto Agent : Agents)
	{
		
	}
}

void AFogOfWarInfo::AddAgent(UFogOfWarAgentComponent* InAgent)
{
	Agents.Add(InAgent);
	OnAddAgent.Broadcast(InAgent);
}

void AFogOfWarInfo::RemoveAgent(UFogOfWarAgentComponent* InAgent)
{
	Agents.RemoveSwap(InAgent);
	OnRemoveAgent.Broadcast(InAgent);
}