// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Symbol.h"
#include "Bow.generated.h"

/**
 * 
 */
UCLASS()
class HEKSY_API ABow : public ASymbol, public IAction
{
	GENERATED_BODY()

public:
	ABow();

	virtual void Action(AUnit* Unit, int32 Side) override;
	
};