// Fill out your copyright notice in the Description page of Project Settings.


#include "FogOfWar/FogOfWar.h"

#include "RTSUnreal.h"

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
	
}

// Called every frame
void AFogOfWar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFogOfWar::Initialize(AMapTileVolume* InMapTileVolume)
{
	MapTileVolume = InMapTileVolume;

	if(!MapTileVolume)
	{
		UE_LOG(LogRTS, Fatal, TEXT("No Find FogOfWarPostProcessVolume Can't Initialize"));
	}
	
	if(!FogOfWarPostProcessVolume)
	{
		UE_LOG(LogRTS, Warning, TEXT("No FogOfWarPostProcessVolume Won't render fog of war"));
	}

}

