// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */


//typedef GameplayEnums::EPlayer EPlayer;

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

/*
class HEKSY_API GameplayEnums
{
public:

	



	GameplayEnums();
	~GameplayEnums();
};
*/