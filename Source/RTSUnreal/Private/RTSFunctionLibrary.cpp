// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSFunctionLibrary.h"
#include "RTSCollisionChannel.h"
#include "RTSGameInstance.h"
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

AActor* URTSFunctionLibrary::LineTraceSingleForSelection(UObject* WorldContextObject, APlayerController* PlayerController, float Distance)
{
	FVector WorldLocation, WorldDirection;
	PlayerController->DeprojectMousePositionToWorld(WorldLocation,WorldDirection);
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::LogAndReturnNull);
	FHitResult Hit;
	FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam;
	FCollisionResponseParams ResponseParam = FCollisionResponseParams::DefaultResponseParam;
	if (World->LineTraceSingleByChannel(Hit, WorldLocation, WorldLocation + Distance * WorldDirection, ECC_RTSSelection, Params, ResponseParam))
	{
		return Hit.GetActor();
	}
	return nullptr;
}