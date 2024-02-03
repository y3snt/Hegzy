/*****************************************************************//**
 * \file   Symbol.cpp
 * \brief  
 * 
 *********************************************************************/

#include "Symbol.h"


// Sets default values
ASymbol::ASymbol()
{
	SymbolEnum = ESymbols::INVALID;
}

// Called when the game starts or when spawned
void ASymbol::BeginPlay()
{
	Super::BeginPlay();
	
}

ESymbols ASymbol::ToEnum() 
{
	return SymbolEnum;
}

void ASymbol::SetSymbolEnum(ESymbols Symbol)
{
	SymbolEnum = Symbol;
}
