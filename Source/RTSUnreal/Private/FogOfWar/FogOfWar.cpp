// Fill out your copyright notice in the Description page of Project Settings.


#include "FogOfWar/FogOfWar.h"

#include "RTSGameInstance.h"
#include "FogOfWar/RTSWorldTileVolume.h"
#include "Engine/PostProcessVolume.h"
#include "RTSUnreal.h"
#include "FogOfWar/FogOfWarAgentComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFogOfWar::AFogOfWar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFogOfWar::BeginPlay()
{
	Super::BeginPlay();
	URTSGameInstance* RTSGameInstance = Cast<URTSGameInstance>(GetGameInstance());
	if (!RTSGameInstance)
		UE_LOG(LogRTS, Fatal, TEXT(" GameInstance not is RTSGameInstance or subclass"));
	RTSGameInstance->SetFogOfWar(this);
}

// Called every frame
void AFogOfWar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Update Agent Visible
	for (auto& Agent : Agents)
	{
		// TODO : CALC Agent visible
	}
	// Update texture.
	if (!RTSWorldTileVolume || !FogOfWarMaterial)
	{
		return;
	}

	int32 SizeInTiles = RTSWorldTileVolume->GridTileNumber;

	for (int32 Y = 0; Y < SizeInTiles; ++Y)
	{
		for (int32 X = 0; X < SizeInTiles; ++X)
		{
			const int i = Y * SizeInTiles + X;

			const int iBlue = i * 4 + 0;
			const int iGreen = i * 4 + 1;
			const int iRed = i * 4 + 2;
			const int iAlpha = i * 4 + 3;

			// switch (VisionInfo->GetVision(X, Y))
			// {
			// case ERTSVisionState::VISION_Visible:
			// 	FogOfWarTextureBuffer[iBlue] = 0;
			// 	FogOfWarTextureBuffer[iGreen] = 0;
			// 	FogOfWarTextureBuffer[iRed] = 255;
			// 	FogOfWarTextureBuffer[iAlpha] = 0;
			// 	break;
			//
			// case ERTSVisionState::VISION_Known:
			// 	FogOfWarTextureBuffer[iBlue] = 0;
			// 	FogOfWarTextureBuffer[iGreen] = 255;
			// 	FogOfWarTextureBuffer[iRed] = 0;
			// 	FogOfWarTextureBuffer[iAlpha] = 0;
			// 	break;
			//
			// case ERTSVisionState::VISION_Unknown:
			// 	FogOfWarTextureBuffer[iBlue] = 0;
			// 	FogOfWarTextureBuffer[iGreen] = 0;
			// 	FogOfWarTextureBuffer[iRed] = 0;
			// 	FogOfWarTextureBuffer[iAlpha] = 0;
			// 	break;
			// }
		}
	}

	FogOfWarTexture->UpdateTextureRegions(0, 1, FogOfWarUpdateTextureRegion, SizeInTiles * 4, 4, FogOfWarTextureBuffer);
}

void AFogOfWar::Initialize(ARTSWorldTileVolume* InRTSWorldTileVolume)
{
	RTSWorldTileVolume = InRTSWorldTileVolume;

	if(!RTSWorldTileVolume)
	{
		UE_LOG(LogRTS, Fatal, TEXT("No Find RTSWorldTileVolume Can't Initialize"));
	}
	
	if(!FogOfWarPostProcessVolume)
	{
		UE_LOG(LogRTS, Warning, TEXT("No FogOfWarPostProcessVolume Won't render fog of war"));
	}
	
	// Setup fog of war buffer.
	const int32 TilesSize = RTSWorldTileVolume->GridTileNumber;
	const FVector RTSWorldSize = RTSWorldTileVolume->GridWorldSize;
	check(TilesSize == TilesSize);
	FogOfWarTextureBuffer = new uint8[TilesSize * TilesSize * 4];
	
	FogOfWarTexture = UTexture2D::CreateTransient(TilesSize, TilesSize);
	FogOfWarTexture->AddToRoot();
	FogOfWarTexture->UpdateResource();
	FogOfWarUpdateTextureRegion = new FUpdateTextureRegion2D(0, 0, 0, 0, TilesSize, TilesSize);

	// Setup fog of war material.
	FogOfWarMaterialInstance = UMaterialInstanceDynamic::Create(FogOfWarMaterial, nullptr);
	FogOfWarMaterialInstance->SetTextureParameterValue(FName("VisibilityMask"), FogOfWarTexture);
	FogOfWarMaterialInstance->SetScalarParameterValue(FName("OneOverWorldSize"), 1.0f / RTSWorldSize.X);
	FogOfWarMaterialInstance->SetScalarParameterValue(FName("OneOverTileSize"), 1.0f / TilesSize);
	
	// Setup fog of war post-process volume.
	FogOfWarPostProcessVolume->AddOrUpdateBlendable(FogOfWarMaterialInstance);
	
}

bool AFogOfWar::RegisterAgent(UFogOfWarAgentComponent* FogOfWarAgentComponent)
{
	Agents.Add(FFogOfWarAgent{FogOfWarAgentComponent->GetOwner(),FogOfWarAgentComponent});
	return true;
}

bool AFogOfWar::DeregisterAgent(UFogOfWarAgentComponent* FogOfWarAgentComponent)
{
	return 0 != Agents.Remove(FFogOfWarAgent{FogOfWarAgentComponent->GetOwner(),FogOfWarAgentComponent});
}

AFogOfWar* AFogOfWar::GetFogOfWar()
{
	URTSGameInstance* RTSGameInstance = Cast<URTSGameInstance>(UGameplayStatics::GetGameInstance(GWorld));
	if (RTSGameInstance)
	{
		return RTSGameInstance->GetFogOfWar();
	}
	return nullptr;
}
