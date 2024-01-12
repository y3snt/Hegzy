// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"

#include "EventHandler.cpp"

#include <functional>

/**
 * 
 */

template <typename... Args> // variadic template - any no of args
class HEKSY_API EventHandler // holds specific function that will be invoked, onEvent call
{
	//GENERATED_BODY()

private:
	std::function<void(Args...)> HandlerFunc;

public:
	EventHandler(const std::function<void(Args...)>& Func); // ?explicit
	~EventHandler();

	void operator()(Args... params) const;  // EventHandler(...) operator overloading
	void operator()(Args... params) const;  // EventHandler(...) operator overloading
};

