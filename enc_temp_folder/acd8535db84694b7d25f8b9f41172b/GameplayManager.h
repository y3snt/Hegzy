// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// Basic Includes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Trick
#include "LevelUtils.h"

// Gameplay Actor
#include "HexGridManager.h"
#include "Unit.h"



#include "GameplayManager.generated.h"

/**
 * 
 */
UCLASS()
class HEKSY_API AGameplayManager : public AActor
{
	GENERATED_BODY()

protected:
	void SpawnUnits();

public:

	UPROPERTY(EditAnywhere, Category = "GameplayProperties|Map")
	AHexGridManager *GridManager;


	UPROPERTY(EditAnywhere, Category = "GameplayProperties|Map")
	TArray<AUnit*> AttackerUnits;
	
	UPROPERTY(EditAnywhere, Category = "GameplayProperties|Map")
	TArray<AUnit*> DefenderUnits;

	void InputListener(FIntPoint Cord);


	void SetupGame();

	void TimerFunction();
	FTimerHandle TimerHandle;
	int32 CallTracker = 3;

	// Sets default values for this actor's properties
	AGameplayManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;   // __ why virtual and override??
};
