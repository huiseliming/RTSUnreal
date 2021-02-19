// Fill out your copyright notice in the Description page of Project Settings.


#include "FogOfWar/FogOfWar.h"

#include "RTSGameInstance.h"
#include "FogOfWar/RTSWorldTileVolume.h"
#include "Engine/PostProcessVolume.h"
#include "RTSUnreal.h"
#include "FogOfWar/FogOfWarAgentComponent.h"
#include "Kismet/GameplayStatics.h"

uint32 GetTypeHash(const FFogOfWarAgent& Thing)
{
	uint32 Hash = FCrc::MemCrc32(&Thing, sizeof(FFogOfWarAgent));
	return Hash;
}

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
	Initialize();
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
		float SightRadius = Agent.FogOfWarAgentComponent->GetSightRadius();
		FIntVector ActorLocationTileXYZ = RTSWorldTileVolume->WorldLocationToTileXYZ(Agent.Actor->GetActorLocation());
		if (Agent.ActorLocationTileXYZ.X == ActorLocationTileXYZ.X &&
			Agent.ActorLocationTileXYZ.Y == ActorLocationTileXYZ.Y &&
			Agent.ActorLocationTileXYZ.Z == ActorLocationTileXYZ.Z)
		{
			continue;
		}
		// Moved to new grid cell.
		Agent.ActorLocationTileXYZ = ActorLocationTileXYZ;

		int32 TileX;
		int32 TileY;
		int32 RadiusXSqr;
		int32 RadiusYSqr;
		int32 LocalTileX;
		int32 LocalTileY;
		
		int32 ActorSightRadiusTile = FMath::FloorToInt(SightRadius / RTSWorldTileVolume->TileWorldSize);
		int32 ActorSightRadiusTileSqr = ActorSightRadiusTile * ActorSightRadiusTile;



		for (int32 RadiusY = -ActorSightRadiusTile; RadiusY <= ActorSightRadiusTile; RadiusY++)
		{
			TileY = ActorLocationTileXYZ.Y + RadiusY;
			RadiusYSqr = RadiusY * RadiusY;
			LocalTileY = RadiusY + ActorSightRadiusTile;

			if (TileY >= 0 && TileY < RTSWorldTileVolume->GridTileNumber)
			{
				for (int32 RadiusX = -ActorSightRadiusTile; RadiusX <= ActorSightRadiusTile; RadiusX++)
				{
					TileX = ActorLocationTileXYZ.X + RadiusX;
					RadiusXSqr = RadiusX * RadiusX;
					LocalTileX = RadiusX + ActorSightRadiusTile;

					// Check if within circle.
					if (TileX >= 0 && TileX < RTSWorldTileVolume->GridTileNumber && (RadiusXSqr + RadiusYSqr <= ActorSightRadiusTileSqr))
					{
						if (Agent.FogOfWarAgentComponent->IsIgnoresHeightLevels()
                            //|| HasLocalVisionAt(LocalTileX, LocalTileY, ActorSightRadiusTile, TileX, TileY,
                            //    ActorLocationTile.X, ActorLocationTile.Y, ActorLocationHeightLevel)
                                )
						{
							WorldTiles[RTSWorldTileVolume->TileXYToTileIndex(TileX, TileY)].AddActor(Agent.Actor);
						}
					}
				}
			}
		}

		// TODO : CALC Agent visible
	}
	// Update texture.
	if (RTSWorldTileVolume == nullptr || FogOfWarMaterial == nullptr)
	{
		return;
	}

	int32 GridTileNumber = RTSWorldTileVolume->GridTileNumber;

	for (int32 Y = 0; Y < GridTileNumber; ++Y)
	{
		for (int32 X = 0; X < GridTileNumber; ++X)
		{
			const int i = Y * GridTileNumber + X;

			const int iBlue = i * 4 + 0;
			const int iGreen = i * 4 + 1;
			const int iRed = i * 4 + 2;
			const int iAlpha = i * 4 + 3;

			if(WorldTiles[X + GridTileNumber * Y].IsVisible())
			{
				FogOfWarTextureBuffer[iBlue] = 0;
				FogOfWarTextureBuffer[iGreen] = 0;
				FogOfWarTextureBuffer[iRed] = 255;
				FogOfWarTextureBuffer[iAlpha] = 0;
			}
			
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

	FogOfWarTexture->UpdateTextureRegions(0, 1, FogOfWarUpdateTextureRegion, GridTileNumber * 4, 4, FogOfWarTextureBuffer);
}

void AFogOfWar::Initialize()
{
	AActor* Actor = UGameplayStatics::GetActorOfClass(GWorld,ARTSWorldTileVolume::StaticClass());
	RTSWorldTileVolume = Cast<ARTSWorldTileVolume>(Actor);
	
	if(RTSWorldTileVolume == nullptr)
	{
		UE_LOG(LogRTS, Fatal, TEXT("No Find RTSWorldTileVolume Can't Initialize"));
	}
	
	RTSWorldTileVolume->Initialize();
	
	if(!FogOfWarPostProcessVolume)
	{
		UE_LOG(LogRTS, Warning, TEXT("No FogOfWarPostProcessVolume Won't render fog of war"));
	}
	
	// Setup fog of war buffer.
	const int32 GridTileNumber = RTSWorldTileVolume->GridTileNumber;
	const FVector RTSWorldSize = RTSWorldTileVolume->GridWorldSize;
	
	FogOfWarTextureBuffer = new uint8[GridTileNumber * GridTileNumber * 4];
	
	for (int32 Y = 0; Y < GridTileNumber; ++Y)
	{
		for (int32 X = 0; X < GridTileNumber; ++X)
		{
			const int i = Y * GridTileNumber + X;

			const int iBlue = i * 4 + 0;
			const int iGreen = i * 4 + 1;
			const int iRed = i * 4 + 2;
			const int iAlpha = i * 4 + 3;

			FogOfWarTextureBuffer[iBlue] = 0;
			FogOfWarTextureBuffer[iGreen] = 0;
			FogOfWarTextureBuffer[iRed] = 0;
			FogOfWarTextureBuffer[iAlpha] = 0;
		}
	}

	WorldTiles.Init(FWorldTiles{0},GridTileNumber * GridTileNumber);
	
	FogOfWarTexture = UTexture2D::CreateTransient(GridTileNumber, GridTileNumber);
	FogOfWarTexture->AddToRoot();
	FogOfWarTexture->UpdateResource();
	FogOfWarUpdateTextureRegion = new FUpdateTextureRegion2D(0, 0, 0, 0, GridTileNumber, GridTileNumber);
	
	// Setup fog of war material.
	FogOfWarMaterialInstance = UMaterialInstanceDynamic::Create(FogOfWarMaterial, nullptr);
	FogOfWarMaterialInstance->SetTextureParameterValue(FName("FogOfWarRenderTarget"), FogOfWarTexture);
	FogOfWarMaterialInstance->SetScalarParameterValue(FName("OneOverWorldSize"), 1.0f / RTSWorldSize.X);
	FogOfWarMaterialInstance->SetScalarParameterValue(FName("WorldXYSize"), RTSWorldSize.X);
	FogOfWarMaterialInstance->SetScalarParameterValue(FName("WorldZSize"), 3000);
	FogOfWarMaterialInstance->SetScalarParameterValue(FName("OneOverTileSize"), 1.0f / GridTileNumber);
	
	
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
