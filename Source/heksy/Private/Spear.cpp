/*****************************************************************//**
 * \file   Spear.cpp
 * \brief  
 * 
 *********************************************************************/
#include "Spear.h"
#include "Effects.h"

ASpear::ASpear() 
{
	SetSymbolEnum(ESymbols::SPEAR);
}

void ASpear::Action(AUnit* Unit, int32 Side)
{
	Effects::AttackAdjacentUnit(Unit, Side, this->ToEnum());
}

void ASpear::PassiveAction(AUnit* Unit, int32 Side)
{
	Effects::AttackAdjacentUnit(Unit, Side, this->ToEnum());
}
