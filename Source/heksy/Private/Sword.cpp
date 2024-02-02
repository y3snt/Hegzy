// Fill out your copyright notice in the Description page of Project Settings.
#include "Sword.h"

#include "HexGridManager.h"



void ASword::Action(AUnit* Unit, int32 Side) // Adjacent Attack
{

	AUnit* Target = AHexGridManager::GetUnit(AHexGridManager::AdjacentCord(Unit->CurrentCord, Side));
	if (Target && Target->Controller != Unit->Controller)
		Target->Damage(Side, this->ToEnum());
}