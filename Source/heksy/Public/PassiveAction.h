/*****************************************************************//**
 * \file   PassiveAction.h
 * \brief  Symbol
 * 
 *********************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Unit.h"

#include "PassiveAction.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable) // ? Blueprintable
class UPassiveAction : public UInterface
{
	GENERATED_BODY()
};

class HEKSY_API IPassiveAction
{
	GENERATED_BODY()

public:
	virtual void PassiveAction(AUnit* Unit, int32 Side) = 0;
};
