// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEnums.h"

class AUnit;

/**
 * 
 */
class HEKSY_API Effects
{
public:
	Effects();
	~Effects();

	static void AttackAdjacentUnit(AUnit* Unit, int32 Side, ESymbols AttackSymbol);
	static void RangedAttack(AUnit* Unit, int32 Side, ESymbols AttackSymbol);
	static void PushUnit(AUnit* Unit, int32 Side, int32 Distance);
};
