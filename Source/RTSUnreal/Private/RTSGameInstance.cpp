// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSGameInstance.h"

AFogOfWar* URTSGameInstance::GetFogOfWar()
{
	return FogOfWar;
}

void URTSGameInstance::SetFogOfWar(AFogOfWar* FogOfWar)
{
	this->FogOfWar = FogOfWar;
}

