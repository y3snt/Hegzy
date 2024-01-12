// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"



#include <functional>

#include "EventHandler.cpp"



/**
 * 
 */

//template <typename... Args> // variadic template - any no of args
class HEKSY_API EventHandler // holds specific function that will be invoked, onEvent call
{
	//GENERATED_BODY()

	//std::function<void(Args...)> HandlerFunc;

public:
	//explicit EventHandler(const std::function<void(Args...)>& Func);
	EventHandler();


	~EventHandler();

	//void operator()(Args... params) const;  // EventHandler(...) operator overloading
};

