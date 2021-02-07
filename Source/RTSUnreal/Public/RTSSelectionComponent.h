// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RTSSelectionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRTSSelectionComponentSelectedSignature, AActor*, Actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRTSSelectionComponentDeselectedSignature, AActor*, Actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRTSSelectionComponentHoveredSignature, AActor*, Actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRTSSelectionComponentUnhoveredSignature, AActor*, Actor);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RTSUNREAL_API URTSSelectionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URTSSelectionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure, Category="RTS|SelectionComponent")
	AActor* GetSelectedActor() { return CurrentSelectedActors.IsValidIndex(CurrentSelectedActorIndex) ? CurrentSelectedActors[CurrentSelectedActorIndex] : nullptr;}
	UFUNCTION(BlueprintPure, Category="RTS|SelectionComponent")
	TArray<AActor*>& GetSelectedActors() { return CurrentSelectedActors; }

	// Delegates
	UPROPERTY(BlueprintAssignable, Category = "RTS|SelectionComponent")
	FRTSSelectionComponentSelectedSignature OnRTSSelectionComponentSelected;
	UPROPERTY(BlueprintAssignable, Category = "RTS|SelectionComponent")
    FRTSSelectionComponentDeselectedSignature OnRTSSelectionComponentDeselected;
	UPROPERTY(BlueprintAssignable, Category = "RTS|SelectionComponent")
    FRTSSelectionComponentHoveredSignature OnRTSSelectionComponentHovered;
	UPROPERTY(BlueprintAssignable, Category = "RTS|SelectionComponent")
    FRTSSelectionComponentUnhoveredSignature OnRTSSelectionComponentUnhovered;

	//
	
	
private:
	UPROPERTY()
	TArray<AActor* > CurrentSelectedActors;
	
	UPROPERTY()
	int32 CurrentSelectedActorIndex;
	
	UPROPERTY()
	AActor* CurrentHoveredActor;

	UPROPERTY()
	TArray<UDecalComponent*> DecalComponents;

	UPROPERTY()
	UMaterialInstance * SelectionCircleMaterialInstance = nullptr;
};
