// Fill out your copyright notice in the Description page of Project Settings.
#include "Fist.h"
#include "HexGridManager.h"
#include "GameplayManager.h"



AFist::AFist() 
{
	SetSymbolEnum(ESymbols::PUSH);
}

void AFist::Action(AUnit* Unit, int32 Side) // Adjacent Attack
{
	AUnit* Target = AHexGridManager::GetUnit(AHexGridManager::AdjacentCord(Unit->CurrentCord, Side));
	if (!Target || Target->Controller == Unit->Controller)
		return;

	EHexTileType BehindTile = AHexGridManager::GetDistantTileType(Unit->CurrentCord, Side, 2);
	AUnit* BehindUnit = AHexGridManager::GetDistantUnit(Unit->CurrentCord, Side, 2);

	// TODO: Move to hex grid MG (which will validate position and kill if on a bad position)
	if (BehindUnit || BehindTile == EHexTileType::SENTINEL)  // Pushing outside the map or in the Unit
	{
		AGameplayManager::KillUnit(Target);
	}
	else if (BehindUnit == nullptr) // Simple push TODO: we don't need else if here, just else
	{
		AHexGridManager::ChangeUnitPosition(Target, AHexGridManager::GetDistantCord(Unit->CurrentCord, Side, 2));
		AGameplayManager::EnemyDamage(Target);
	}
}