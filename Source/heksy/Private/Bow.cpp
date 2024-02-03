/*****************************************************************//**
 * \file   Bow.cpp
 * \brief  
 * 
 *********************************************************************/
#include "Bow.h"
#include "Effects.h"


ABow::ABow()
{
    SetSymbolEnum(ESymbols::BOW);
}

void ABow::Action(AUnit* Unit, int32 Side)
{
	Effects::RangedAttack(Unit, Side, this->ToEnum());
}