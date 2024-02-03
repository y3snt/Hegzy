/*****************************************************************//**
 * \file   GameplayEnums.h
 * \brief  List of Enums used in gameplay throught the project
 *********************************************************************/
#pragma once

#include "CoreMinimal.h"



UENUM()
enum class EHexTileType : uint8  // __ why uint?
{
	INVALID,
	SENTINEL,
	ATTACKER_SPAWN,
	DEFENDER_SPAWN,
	DEFAULT,
	MAX UMETA(Hidden)  // __ ???
};


UENUM()
enum class EPlayer : uint8  // __ why uint?
{
	INVALID,
	ATTACKER,
	DEFENDER,
	MAX UMETA(Hidden)  // __ ???
};

UENUM()
enum class ESymbols : uint8  // __ why uint?
{
	INVALID,
	SPEAR,
	SWORD,
	SHIELD,
	BOW,
	PUSH,
	MAX UMETA(Hidden)  // __ ???
};

