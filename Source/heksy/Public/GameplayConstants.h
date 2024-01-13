// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */




class HEKSY_API GameplayConstants
{
public:
	GameplayConstants();
	~GameplayConstants();

	const TArray<FIntPoint> Directions = {
			FIntPoint(1, 0),
			FIntPoint(0, 1),
			FIntPoint(-1, 1),
			FIntPoint(-1, 0),
			FIntPoint(0, -1),
			FIntPoint(1, -1) };


	//static const TArray<FIntPoint> Directions; // const 
	
};
