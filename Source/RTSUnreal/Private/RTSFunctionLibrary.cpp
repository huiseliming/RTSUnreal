// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSFunctionLibrary.h"

#include "Kismet/GameplayStatics.h"

// FVector URTSFunctionLibrary::GetCursorWorldPlacement(UObject* WorldContextObject, APlayerController* PlayerController, float Distance)
// {
// 	FVector WorldLocation, WorldDirection;
// 	PlayerController->DeprojectMousePositionToWorld(WorldLocation,WorldDirection);
// 	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::LogAndReturnNull);
// 	FHitResult Hit;
// 	if (World->LineTraceSingleByChannel(Hit,WorldLocation,WorldLocation + Distance * WorldDirection, ECollisionChannel::ECC_Visibility))
// 	{
// 			return Hit.Location;
// 	}
// 	return FVector();
// }
