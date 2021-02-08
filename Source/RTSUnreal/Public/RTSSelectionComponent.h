// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RTSSelectionComponent.generated.h"

class ARTSPlayerController;
class ARTSHUD;

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
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category="RTS|SelectionComponent")
	void Select();
	UFUNCTION(BlueprintCallable, Category="RTS|SelectionComponent")
	void SelectBox(FVector2D FirstPoint, FVector2D SecondPoint);

	UFUNCTION(BlueprintPure, Category="RTS|SelectionComponent")
	AActor* GetSelectedActor() { return CurrentSelectedActors.IsValidIndex(CurrentSelectedActorIndex) ? CurrentSelectedActors[CurrentSelectedActorIndex] : nullptr;}
	UFUNCTION(BlueprintPure, Category="RTS|SelectionComponent")
	TArray<AActor*>& GetSelectedActors() { return CurrentSelectedActors; }

	// Delegates
	UPROPERTY(BlueprintAssignable, Category = "RTS|SelectionComponent")
	FRTSSelectionComponentSelectedSignature OnRTSSelectionSelected;
	UPROPERTY(BlueprintAssignable, Category = "RTS|SelectionComponent")
    FRTSSelectionComponentDeselectedSignature OnRTSSelectionDeselected;
	UPROPERTY(BlueprintAssignable, Category = "RTS|SelectionComponent")
    FRTSSelectionComponentHoveredSignature OnRTSSelectionHovered;
	UPROPERTY(BlueprintAssignable, Category = "RTS|SelectionComponent")
    FRTSSelectionComponentUnhoveredSignature OnRTSSelectionUnhovered;

	//
	UPROPERTY(EditDefaultsOnly, Category="RTS|SelectionComponent")
	bool bSelectBoxIncludeNonCollidingComponents = true;
	UPROPERTY(EditDefaultsOnly, Category="RTS|SelectionComponent")
	bool bSelectBoxActorMustBeFullyEnclosed = false;
	
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

	UPROPERTY()
	ARTSPlayerController* RTSPlayerController = nullptr;
	
	UPROPERTY()
	ARTSHUD* RTSHUD = nullptr;
	
};
