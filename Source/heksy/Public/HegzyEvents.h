// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"

#include <functional>

#include "HegzyEvents.cpp"


/**
 * 
 */
//template <typename... Args> // variadic template - any no of args
class HEKSY_API HegzyEvents
{
	//std::function<void(Args...)> HandlerFunc;

public:
	//explicit HegzyEvents(const std::function<void(Args...)>& Func);
	HegzyEvents();
	~HegzyEvents();
};
