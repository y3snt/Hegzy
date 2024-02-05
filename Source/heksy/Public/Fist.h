/*****************************************************************//**
 * \file   Fist.h
 * \brief  Symbol
 * 
 *********************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Symbol.h"
#include "Fist.generated.h"

UCLASS()
class HEKSY_API AFist : public ASymbol, public IAction
{
	GENERATED_BODY()

public:
	AFist();

	virtual void Action(AUnit* Unit, int32 Side) override;
};