// Fill out your copyright notice in the Description page of Project Settings.
#include "Sword.h"

#include "Effects.h"

ASword::ASword() 
{
	SetSymbolEnum(ESymbols::SWORD);
}

void ASword::Action(AUnit* Unit, int32 Side)
{
	Effects::AttackAdjacentUnit(Unit, Side, this->ToEnum());
}