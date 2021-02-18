// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "FogOfWar.generated.h"

class APostProcessVolume;
class ARTSWorldTileVolume;
USTRUCT()
struct RTSUNREAL_API FWorldTiles
{
	GENERATED_BODY()

	void AddActor(AActor* Actor) { ++ActorNumber; }
	void RemoveActor(AActor* Actor) { --ActorNumber; }
	bool IsVisible() { return ActorNumber > 0; }
	
	int32 ActorNumber;
};

class UFogOfWarAgentComponent;

USTRUCT()
struct RTSUNREAL_API FFogOfWarAgent
{
	GENERATED_BODY()
	
	UPROPERTY()
	AActor* Actor;
	
	UPROPERTY()
	UFogOfWarAgentComponent* FogOfWarAgentComponent;
	
	bool operator==(const FFogOfWarAgent& Other) const
	{
		return Equals(Other);
	}

	bool Equals(const FFogOfWarAgent& Other) const
	{
		return Actor == Other.Actor && FogOfWarAgentComponent == Other.FogOfWarAgentComponent;
	}

};

uint32 GetTypeHash(const FFogOfWarAgent& Thing);

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

public:
	
	void Initialize();

	
	
	UPROPERTY(EditInstanceOnly, Category="RTS|FogOfWar")
	APostProcessVolume* FogOfWarPostProcessVolume;
	
	UPROPERTY()
	ARTSWorldTileVolume* RTSWorldTileVolume;

	
	// Material for rendering the fog of war effect
	UPROPERTY(EditInstanceOnly, Category = "RTS")
	UMaterialInterface* FogOfWarMaterial;

	UPROPERTY()
	UTexture2D* FogOfWarTexture;

	uint8* FogOfWarTextureBuffer;
	
	/** Update region for updating the contents of the fog of war texture. */
	FUpdateTextureRegion2D* FogOfWarUpdateTextureRegion;

	/** Post-process material instance for rendering fog of war in 3D space. */
	UPROPERTY()
	UMaterialInstanceDynamic* FogOfWarMaterialInstance;
	
	UPROPERTY()
	TArray<FWorldTiles> WorldTiles;
		
	UFUNCTION(BlueprintPure, Category = "RTS|FogOfWar")
    static AFogOfWar* GetFogOfWar();
	
private:
	TSet<FFogOfWarAgent> Agents;
public:
	bool RegisterAgent(UFogOfWarAgentComponent* FogOfWarAgentComponent);
	bool DeregisterAgent(UFogOfWarAgentComponent* FogOfWarAgentComponent);
	
};
