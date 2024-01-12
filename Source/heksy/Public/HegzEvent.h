// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
template<class... Args>
class HEKSY_API HegzEvent
{
public:	
	void operator()(Args... params) const;
	HegzEvent<Args...>& operator+=(const std::function<void(Args...)>& handler);  // ew. check if same handler is not added twice... but ==
	HegzEvent<Args...>& operator+=(const EventHandler<Args...>& handler);
	bool operator-=(const EventHandler<Args...>& handler);

protected:
	void Add(const std::function<void(Args...)>& handler);
	void AddHandler(const EventHandler<Args...>& handler);
	bool RemoveHandler(const EventHandler<Args...>& handler);

    std::list< EventHandler<Args...> > Handlers;
};
