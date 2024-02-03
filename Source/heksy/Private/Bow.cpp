// Fill out your copyright notice in the Description page of Project Settings.
#include "Bow.h"
#include "HexGridManager.h"



ABow::ABow()
{
    SetSymbolEnum(ESymbols::BOW);
}

void ABow::Action(AUnit* Unit, int32 Side)
{
	AUnit* Target = AHexGridManager::GetShotTarget(Unit->CurrentCord, Side);
	if (Target && Target->Controller != Unit->Controller)
		Target->Damage(Side, this->ToEnum());
}