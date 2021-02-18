// Fill out your copyright notice in the Description page of Project Settings.


#include "FogOfWar/FogOfWarAgentComponent.h"

#include "FogOfWar/FogOfWar.h"

// Sets default values for this component's properties
UFogOfWarAgentComponent::UFogOfWarAgentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFogOfWarAgentComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFogOfWarAgentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UFogOfWarAgentComponent::Activate(bool bReset)
{
	AFogOfWar::GetFogOfWar()->RegisterAgent(this);
}

void UFogOfWarAgentComponent::Deactivate()
{
	AFogOfWar::GetFogOfWar()->DeregisterAgent(this);
}

