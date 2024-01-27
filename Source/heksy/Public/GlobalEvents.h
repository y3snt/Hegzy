// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "HegzEvent.h"
#include "Unit.h"

#include "UObject/NoExportTypes.h"
#include "GlobalEvents.generated.h"

/**
 * 
 */
UCLASS()
class HEKSY_API UGlobalEvents : public UObject
{
	GENERATED_BODY()
public:
	static inline HegzEvent<int> OnUnitMoved;
	static inline HegzEvent<AUnit*> OnUnitDeath;

	//GlobalEvents();
	//~GlobalEvents();
};
