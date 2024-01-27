// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//#include "CoreMinimal.h"



#include "EventHandler.cpp"



// #include <functional>

/**
 * Since it is a template class, implementation is inside .h file
 */

template <class... Args> // variadic template - any no of args
//UCLASS()
class HEKSY_API EventHandler// : public UObject // holds specific function that will be invoked, onEvent call
{
	//GENERATED_BODY()

private:
	TFunction<void(Args...)> HandlerFunc;

public:
	//EventHandler(const TFunction<void(Args...)>& Func); // ?explicit

	EventHandler(const TFunction<void(Args...)>& Func) : HandlerFunc(Func) {}
	//EventHandler(const void(*Func)(inargs...)); // ?explicit
	//EventHandler(const std::function<void(Args...)>& Func); // ?explicit

	//~EventHandler();

	//void operator()(Args... params) const;  // EventHandler(...) operator overloading
	void operator()(Args... params) const  // EventHandler(...) operator overloading
	{
		if (HandlerFunc)
		{
			HandlerFunc(params...);
		}
	}

};