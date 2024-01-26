// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Symbol.generated.h"

UCLASS()
class HEKSY_API ASymbol : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASymbol();

	//UPROPERTY(EditAnywhere, Category = "HexGrid|Effects")
	//TArray<TSubclassOf<AEffect>> EffectList;


	void Action();

	void Block();

	void Passive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
