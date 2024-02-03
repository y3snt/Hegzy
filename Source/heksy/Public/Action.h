/*****************************************************************//**
 * \file   Action.h
 * \brief  Basic Interface for Actionable classes
 * 
 *********************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Unit.h"
#include "Action.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable) // ? Blueprintable
class UAction : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HEKSY_API IAction
{
	GENERATED_BODY()

public:
	virtual void Action(AUnit* Unit, int32 Side) = 0; 
};
