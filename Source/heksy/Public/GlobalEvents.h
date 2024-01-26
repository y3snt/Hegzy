// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "HegzEvent.h"
#include "Unit.h"


/**
 * 
 */
class HEKSY_API GlobalEvents
{
public:
	static inline HegzEvent<int> OnUnitMoved;
	static inline HegzEvent<AUnit*> OnUnitDeath;

	GlobalEvents();
	~GlobalEvents();
};
