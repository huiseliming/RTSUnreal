// Fill out your copyright notice in the Description page of Project Settings.


#include "War3GameState.h"

AWar3GameState::AWar3GameState()
{
	// GameState default disable Tick, so enable tick
	PrimaryActorTick.bCanEverTick = true;
}

void AWar3GameState::BeginPlay()
{
	Super::BeginPlay();
}

void AWar3GameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	// Calculate GameTime
	//GameTimeSeconds = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());
	GameTimeSeconds += DeltaSeconds * GameSpeed;
	const float DaySeconds = 24.f * 60.f * 60.f;
	if (GameTimeSeconds > DaySeconds)
	{
		GameTimeSeconds -= DaySeconds;
		GameDay += 1;
	}
	//GLog->Log(FString::Printf(TEXT("%f"), GameTimeSeconds));
	// Update sun direction
	
}

void AWar3GameState::GetGameTime(float& GameTime, int32& Day, int32& Hour, int32& Minute, int32& Second)
{
	GameTime = this->GameTimeSeconds;
	Day = this->GameDay;
	//GLog->Log(FString::Printf(TEXT("%f"), GameTime));
	Hour  = FMath::FloorToInt(GameTime / 3600.f);
	const float MinuteSeconds= GameTime - Hour * 3600.f;
	Minute = FMath::FloorToInt(MinuteSeconds / 60.f);
	const float SecondSeconds = MinuteSeconds - (Minute * 60.f);
	Second = FMath::FloorToInt(SecondSeconds);
}

