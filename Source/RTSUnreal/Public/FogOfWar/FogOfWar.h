// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FogOfWar.generated.h"

class APostProcessVolume;
class AMapTileVolume;

USTRUCT()
struct RTSUNREAL_API FMapTile
{
	GENERATED_BODY()

	void AddActor(AActor* Actor) { ++ActorNumber; }
	void RemoveActor(AActor* Actor) { --ActorNumber; }
	bool IsVisible() { return ActorNumber > 0; }
	
	int32 ActorNumber;
};

UCLASS()
class RTSUNREAL_API AFogOfWar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFogOfWar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Initialize(AMapTileVolume* InMapTileVolume);


	UPROPERTY(EditInstanceOnly, Category="RTS|FogOfWar")
	APostProcessVolume* FogOfWarPostProcessVolume;
	
	UPROPERTY()
	AMapTileVolume* MapTileVolume;

	UPROPERTY()
	UTexture2D* FogOfWarTexture;

	UPROPERTY()
	TArray<FMapTile> MapTiles;

};
