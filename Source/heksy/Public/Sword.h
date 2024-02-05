/*****************************************************************//**
 * \file   Sword.h
 * \brief  Symbol
 * 
 *********************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Symbol.h"
#include "Sword.generated.h"

UCLASS()
class HEKSY_API ASword : public ASymbol, public IAction
{
	GENERATED_BODY()

public:
	ASword();

	virtual void Action(AUnit* Unit, int32 Side) override;
};
