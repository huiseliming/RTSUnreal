// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSSelectionComponent.h"


#include "RTSHUD.h"
#include "RTSPlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
URTSSelectionComponent::URTSSelectionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URTSSelectionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	RTSPlayerController = Cast<ARTSPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	RTSHUD = Cast<ARTSHUD>(RTSPlayerController->GetHUD());
}

void URTSSelectionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (auto CurrentSelectedActor : CurrentSelectedActors)
		OnRTSSelectionDeselected.Broadcast(CurrentSelectedActor);
	CurrentSelectedActors.Empty();
}


// Called every frame
void URTSSelectionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	
}

void URTSSelectionComponent::Select()
{
	for (auto CurrentSelectedActor : CurrentSelectedActors)
		OnRTSSelectionDeselected.Broadcast(CurrentSelectedActor);
	CurrentSelectedActors.Empty();
	CurrentSelectedActors.Add(CurrentHoveredActor);
	for (auto CurrentSelectedActor : CurrentSelectedActors)
		OnRTSSelectionSelected.Broadcast(CurrentSelectedActor);
}

void URTSSelectionComponent::SelectBox(FVector2D FirstPoint, FVector2D SecondPoint)
{
	for (auto CurrentSelectedActor : CurrentSelectedActors)
		OnRTSSelectionDeselected.Broadcast(CurrentSelectedActor);
	CurrentSelectedActors.Empty();
	RTSHUD->GetActorsInSelectionRectangle(AActor::StaticClass(), FirstPoint, SecondPoint,CurrentSelectedActors, bSelectBoxIncludeNonCollidingComponents, bSelectBoxActorMustBeFullyEnclosed);
	for (auto CurrentSelectedActor : CurrentSelectedActors)
		OnRTSSelectionSelected.Broadcast(CurrentSelectedActor);
}


