// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RTSFunctionLibrary.generated.h"



class ARTSUnit;

/**
 * 
 */
UCLASS()
class RTSUNREAL_API URTSFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintPure, Category = "RTS|FunctionLibrary", meta = (WorldContext = WorldContextObject))
	static AActor* LineTraceSingleForSelection(UObject* WorldContextObject, APlayerController* PlayerController, float Distance);

	//UFUNCTION(BlueprintCallable, Category = "RTSFunctionLibrary", meta = (WorldContext = WorldContextObject))
	//static FVector GetCursorWorldPlacement(UObject* WorldContextObject, APlayerController* PlayerController, float Distance);
	
};
