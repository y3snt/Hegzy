// Fill out your copyright notice in the Description page of Project Settings.
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