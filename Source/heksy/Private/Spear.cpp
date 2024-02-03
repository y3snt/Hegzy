// Fill out your copyright notice in the Description page of Project Settings.
#include "Spear.h"
#include "HexGridManager.h"



ASpear::ASpear() 
{
	SetSymbolEnum(ESymbols::SPEAR);
}

void ASpear::Action(AUnit* Unit, int32 Side)
{
	AUnit* Target = AHexGridManager::GetUnit(AHexGridManager::AdjacentCord(Unit->CurrentCord, Side));
	if (Target && Target->Controller != Unit->Controller)
		Target->Damage(Side, this->ToEnum());
}

void ASpear::PassiveAction(AUnit* Unit, int32 Side)
{
	AUnit* Target = AHexGridManager::GetUnit(AHexGridManager::AdjacentCord(Unit->CurrentCord, Side));
	if (Target && Target->Controller != Unit->Controller)
		Target->Damage(Side, this->ToEnum());
}
