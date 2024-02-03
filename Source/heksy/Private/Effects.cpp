/*****************************************************************//**
 * \file   Effects.cpp
 * \brief  
 * 
 *********************************************************************/
#include "Effects.h"

#include "GameplayManager.h"
#include "HexGridManager.h"


Effects::Effects()
{
}

Effects::~Effects()
{
}

void Effects::AttackAdjacentUnit(AUnit* Unit, int32 Side, ESymbols AttackSymbol)
{
    AUnit* Target = AHexGridManager::GetUnit(AHexGridManager::AdjacentCord(Unit->CurrentCord, Side));
	if (Target && Target->Controller != Unit->Controller)
		Target->Damage(Side, AttackSymbol);
}

void Effects::RangedAttack(AUnit* Unit, int32 Side, ESymbols AttackSymbol) 
{
    AUnit* Target = AHexGridManager::GetShotTarget(Unit->CurrentCord, Side);
	if (Target && Target->Controller != Unit->Controller)
		Target->Damage(Side, AttackSymbol);
}

void Effects::PushUnit(AUnit* Unit, int32 Side, int32 Distance) 
{
    AUnit* Target = AHexGridManager::GetUnit(AHexGridManager::AdjacentCord(Unit->CurrentCord, Side));
	if (!Target || Target->Controller == Unit->Controller)
		return;

	EHexTileType BehindTile = AHexGridManager::GetDistantTileType(Unit->CurrentCord, Side, Distance);
	AUnit* BehindUnit = AHexGridManager::GetDistantUnit(Unit->CurrentCord, Side, Distance);

	// TODO: Move to hex grid MG (which will validate position and kill if on a bad position)
	if (BehindUnit || BehindTile == EHexTileType::SENTINEL)  // Pushing outside the map or in the Unit
	{
		AGameplayManager::KillUnit(Target);
	}
	else if (BehindUnit == nullptr) // Simple push TODO: we don't need else if here, just else
	{
		AHexGridManager::ChangeUnitPosition(Target, AHexGridManager::GetDistantCord(Unit->CurrentCord, Side, Distance));
		AGameplayManager::EnemyDamage(Target);
	}
}