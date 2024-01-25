// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventHandler.h"


/**
 * 
 */
template<class... Args>
class HEKSY_API HegzEvent
{
	//GENERATED_BODY()

public:	
	void operator()(Args... params) const
	{
		for (const auto& handler : Handlers)
		{
			handler(params...);
		}
	}
	
	inline HegzEvent<Args...>& operator+=(const TFunction<void(Args...)>& handler)  // ew. check if same handler is not added twice... but ==
	{
		Add(handler);
		return *this;
	}
  // ew. check if same handler is not added twice... but ==
	HegzEvent<Args...>& operator+=(const EventHandler<Args...>& handler)
	{
		AddHandler(handler);
		return *this;
	}

/*
	inline bool operator-=(const EventHandler<Args...>& handler)
	{
		return RemoveHandler(handler);
	}
	*/

protected:
	inline void Add(const TFunction<void(Args...)>& handler)  // ? remove explicit
	{
		AddHandler(EventHandler<Args...>(handler));
	}

	void AddHandler(const EventHandler<Args...>& handler)
	{
		Handlers.Emplace(handler);
	}

/*
	bool RemoveHandler(const EventHandler<Args...>& handler)
	{
		auto it = Handlers.Find(handler);
		if (it != INDEX_NONE)
		{
			//TODO: Handlers.erase(it);
			return true;
		}

		return false;
	}
	*/

    TArray< EventHandler<Args...> > Handlers;
};
