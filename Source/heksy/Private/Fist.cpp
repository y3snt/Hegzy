/*****************************************************************//**
 * \file   Fist.cpp
 * \brief  
 * 
 *********************************************************************/
#include "Fist.h"
#include "Effects.h"

AFist::AFist() 
{
	SetSymbolEnum(ESymbols::PUSH);
}

void AFist::Action(AUnit* Unit, int32 Side) // Adjacent Attack
{
	Effects::PushUnit(Unit, Side, 2);
}