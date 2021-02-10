// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSHUD.h"


#include "RTSFunctionLibrary.h"
#include "RTSUnit.h"
#include "RTSPlayerController.h"
#include "RTSUnreal.h"

void ARTSHUD::BeginPlay()
{
	Super::BeginPlay();
	RTSPlayerController = Cast<ARTSPlayerController>(GetOwningPlayerController());
	if(!RTSPlayerController)
		UE_LOG(RTSLog, Fatal, TEXT("OwningPlayerController is not a RTSPlayerController "));
}

void ARTSHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for(auto HoveredActor : CurrentHoveredActors){
		OnRTSSelectionHovered.Broadcast(HoveredActor);
	}
	CurrentHoveredActors.Empty();
	for(auto SelectedActor : CurrentSelectedActors){
		OnRTSSelectionDeselected.Broadcast(SelectedActor);
	}
	CurrentSelectedActors.Empty();
}

void ARTSHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ARTSHUD::DrawHUD()
{
	Super::DrawHUD();
	//Update selection box
	if(RTSPlayerController->GetMousePosition(SelectionRectangleEnd.X, SelectionRectangleEnd.Y))
	{
		if (bSelectionUpdate)
		{
			const float ScreenX = SelectionRectangleStart.X < SelectionRectangleEnd.X ? SelectionRectangleStart.X : SelectionRectangleEnd.X ;
			const float ScreenY = SelectionRectangleStart.Y < SelectionRectangleEnd.Y ? SelectionRectangleStart.Y : SelectionRectangleEnd.Y ;
			const float Width = FMath::Abs(SelectionRectangleEnd.X - SelectionRectangleStart.X);
			const float Height = FMath::Abs(SelectionRectangleStart.Y - SelectionRectangleEnd.Y);
			//GLog->Log(FString::Printf(TEXT("ScreenX: %f, ScreenY: %f, Width: %f, Height: %f"), ScreenX, ScreenY, Width, Height));
			DrawRect(FLinearColor(0.5,0.5,0.5,0.3), ScreenX, ScreenY, Width, Height);
			DrawLine(ScreenX, ScreenY, ScreenX +Width, ScreenY, FLinearColor::Gray);
			DrawLine(ScreenX +Width, ScreenY,ScreenX + Width, ScreenY + Height, FLinearColor::Gray);
			DrawLine(ScreenX + Width, ScreenY + Height, ScreenX, ScreenY + Height, FLinearColor::Gray);
			DrawLine(ScreenX, ScreenY + Height, ScreenX, ScreenY, FLinearColor::Gray);
			
			// Set RTS SelectedActorClass for find it 
			const static TArray<UClass*> SelectedActorClassFilters = {ARTSUnit::StaticClass()};
			TArray<AActor*> OldHoveredActors;
			OldHoveredActors.Reset();
			Swap(CurrentHoveredActors,OldHoveredActors);
			TArray<AActor*> Actors;
			for (UClass* ActorClass: SelectedActorClassFilters)
			{
				GetActorsInSelectionRectangle(ActorClass ,SelectionRectangleStart, SelectionRectangleEnd,Actors,false ,false);
				CurrentHoveredActors.Append(Actors);
			}
			// handle Hovered and Unhovered Event;
			Algo::Sort(CurrentHoveredActors,[](const AActor* A, const AActor* B)
                {
                    return  reinterpret_cast<uint64>(A) < reinterpret_cast<uint64>(B);
                });
			if(CurrentHoveredActors.Num() == 0)
			{
				for (AActor* Actor : OldHoveredActors)
				{
					OnRTSSelectionUnhovered.Broadcast(Actor);
					UE_LOG(RTSLog, Display, TEXT("remove %s"), *Actor->GetName());
				}
			}
			else
			{
				int32 CurrentHoveredActorsIndex = 0;
				for (int32 i = 0; i < OldHoveredActors.Num(); i++)
				{
					while (CurrentHoveredActorsIndex < CurrentHoveredActors.Num() && reinterpret_cast<uint64>(OldHoveredActors[i]) > reinterpret_cast<uint64>(CurrentHoveredActors[CurrentHoveredActorsIndex]))
					{
						OnRTSSelectionHovered.Broadcast(CurrentHoveredActors[CurrentHoveredActorsIndex]);
						UE_LOG(RTSLog, Display, TEXT("add %s"), *CurrentHoveredActors[CurrentHoveredActorsIndex]->GetName());
						CurrentHoveredActorsIndex++;
					}
					if(CurrentHoveredActorsIndex >= CurrentHoveredActors.Num())
					{
						OnRTSSelectionUnhovered.Broadcast(OldHoveredActors[i]);
						UE_LOG(RTSLog, Display, TEXT("remove %s"), *OldHoveredActors[i]->GetName());
						continue;
					}
					if(reinterpret_cast<uint64>(OldHoveredActors[i]) < reinterpret_cast<uint64>(CurrentHoveredActors[CurrentHoveredActorsIndex]))
					{
						OnRTSSelectionUnhovered.Broadcast(OldHoveredActors[i]);
						UE_LOG(RTSLog, Display, TEXT("remove %s"), *OldHoveredActors[i]->GetName());
					}
					else if(reinterpret_cast<uint64>(OldHoveredActors[i]) == reinterpret_cast<uint64>(CurrentHoveredActors[CurrentHoveredActorsIndex]))
					{
						CurrentHoveredActorsIndex++;
					}
				}
				while (CurrentHoveredActorsIndex < CurrentHoveredActors.Num())
				{
					OnRTSSelectionHovered.Broadcast(CurrentHoveredActors[CurrentHoveredActorsIndex]);
					UE_LOG(RTSLog, Display, TEXT("add %s"), *CurrentHoveredActors[CurrentHoveredActorsIndex]->GetName());
					CurrentHoveredActorsIndex++;
				}
			}
		}
		else
		{
			// SingleSelect Hovered Logic
			AActor* Actor = URTSFunctionLibrary::LineTraceSingleForSelection(GetWorld(),RTSPlayerController,30000.0f);
			if (Actor != nullptr)
			{
				if(!(CurrentHoveredActors.Num() == 1 && CurrentHoveredActors[0] == Actor))
				{
					if (CurrentHoveredActors.Num() != 0)
					{
						for (AActor* HoveredActor : CurrentHoveredActors)
							OnRTSSelectionUnhovered.Broadcast(HoveredActor);
						CurrentHoveredActors.Empty();
					}
					CurrentHoveredActors.Empty();
					CurrentHoveredActors.Add(Actor);
					OnRTSSelectionHovered.Broadcast(Actor);
				}
			}
			else
			{
				if(CurrentHoveredActors.Num() != 0)
				{
					for (AActor* HoveredActor : CurrentHoveredActors)
						OnRTSSelectionUnhovered.Broadcast(HoveredActor);
					CurrentHoveredActors.Empty();
				}
			}
		}
		if (bSelectionFinish)
		{
			bSelectionFinish = false;
			BoxSelect();
			for (AActor* Actor : CurrentHoveredActors)
			{
				OnRTSSelectionUnhovered.Broadcast(Actor);
			}
			CurrentHoveredActors.Empty();
		}
	}
}

void ARTSHUD::SingleSelect()
{
	for (auto Actor : CurrentSelectedActors)
		OnRTSSelectionDeselected.Broadcast(Actor);
	CurrentSelectedActors.Empty();
	if (CurrentHoveredActors.IsValidIndex(0) && CurrentHoveredActors[0] != nullptr)
	{
		AActor* CurrentHoveredActor = CurrentHoveredActors[0];
		UE_LOG(RTSLog, Display, TEXT("SingleSelect Actor %s"), *CurrentHoveredActor->GetName());
		CurrentSelectedActors.Add(CurrentHoveredActor);
		OnRTSSelectionSelected.Broadcast(CurrentHoveredActor);
		CurrentSelectedActor = CurrentSelectedActors[0];
	}
	else
	{
		CurrentSelectedActor = nullptr;
	}
}

void ARTSHUD::BoxSelect()
{
	for (auto Actor : CurrentSelectedActors)
		OnRTSSelectionDeselected.Broadcast(Actor);
	CurrentSelectedActors.Empty();
	UE_LOG(RTSLog, Display, TEXT("BoxSelect Actor Count %d"), CurrentHoveredActors.Num());
	for (auto Actor : CurrentHoveredActors)
	{
		CurrentSelectedActors.Add(Actor);
		OnRTSSelectionSelected.Broadcast(Actor);
		UE_LOG(RTSLog, Display, TEXT("BoxSelect Actor %s"), *Actor->GetName());
	}
	if (CurrentSelectedActors.IsValidIndex(0))
		CurrentSelectedActor = CurrentSelectedActors[0];
	else
		CurrentSelectedActor = nullptr;
}

void ARTSHUD::StartSelectionRectangle()
{
	bSelectionUpdate = true;
	bSelectionFinish = false;
	if (RTSPlayerController->GetMousePosition(SelectionRectangleStart.X, SelectionRectangleStart.Y))
		SelectionRectangleEnd = SelectionRectangleStart;
}

void ARTSHUD::FinishSelectionRectangle()
{
	//UE_LOG(RTSLog, Display, TEXT("FinishSelectionRectangle"));
	bSelectionUpdate = false;
	if(RTSPlayerController->GetMousePosition(SelectionRectangleEnd.X, SelectionRectangleEnd.Y))
	{
		if ((SelectionRectangleEnd - SelectionRectangleStart).SizeSquared() > 9)
			bSelectionFinish = true;
		else
			SingleSelect();
	}
}

TArray<AActor*>& ARTSHUD::GetSelectedActors()
{
	return CurrentSelectedActors;
}

TArray<AActor*>& ARTSHUD::GetHoveredActors()
{
	return CurrentHoveredActors;
}
