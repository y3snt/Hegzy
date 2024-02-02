// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Unit.h"
#include "Action.h"

#include "Symbol.generated.h"

//class AUnit;

UCLASS()
class HEKSY_API ASymbol : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASymbol();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};


// Sword.h
/*
UCLASS(Blueprintable, Category = "MyGame")
class ASword : public AActor, public IAction
{
	GENERATED_BODY()

public:
	virtual void Action(AUnit* Unit, int32 Side) override;
};

*/