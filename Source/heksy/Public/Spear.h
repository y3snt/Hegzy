// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Symbol.h"
#include "Spear.generated.h"

/**
 * 
 */
UCLASS()
class HEKSY_API ASpear : public ASymbol, public IAction, public IPassiveAction
{
	GENERATED_BODY()

public:
	ASpear();

	virtual void Action(AUnit* Unit, int32 Side) override;
	virtual void PassiveAction(AUnit* Unit, int32 Side) override;
	
};