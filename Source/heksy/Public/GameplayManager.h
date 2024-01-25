// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// Basic Includes
//#include "GameplayHeader.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Trick
#include "LevelUtils.h"
#include "Kismet/KismetMathLibrary.h"  // Max3 Function

// Gameplay Actor
#include "HexGridManager.h"
#include "Unit.h"

#include "GameplayEnums.h"



#include "GameplayManager.generated.h"

/**
 * 
 */


UENUM()
enum class EAutomaticTestsList : uint8  // __ why uint?
{
	INVALID,
	EMPTY,
	BASIC_UNIT_SETUP,
	MAX UMETA(Hidden)  // __ ???
};


UCLASS()
class HEKSY_API AGameplayManager : public AActor
{
	GENERATED_BODY()

protected:
	void SpawnUnits();

	int32 UnitsLeftToBeSummoned;

	EPlayer CurrentPlayer = EPlayer::ATTACKER;

	AUnit* SelectedUnit;


	UPROPERTY(EditAnywhere, Category = "AutomaticTests|Basic")   // __ ? we can change the value of a blueprint later
	EAutomaticTestsList AutomaticTest;

	void SimpleAutomaticTests();
	bool SelectUnit(const FIntPoint& Cord);

public:

	UPROPERTY(EditAnywhere, Category = "GameplayProperties|Map")
	AHexGridManager *GridManager;  // TODO: singleton, SMART POINTERS!!!


	UPROPERTY(EditAnywhere, Category = "GameplayProperties|Map")
	TArray<AUnit*> AttackerUnits;
	
	UPROPERTY(EditAnywhere, Category = "GameplayProperties|Map")
	TArray<AUnit*> DefenderUnits;


	void InputListener(FIntPoint Cord);

	

	void SummonUnit(FIntPoint Cord);
	void SetupGame();

	void SwitchPlayerTurn();

	void Gameplay(FIntPoint Cord);

	bool IsLegalMove(FIntPoint Cord, int32& ResultSide);

	bool SymbolAttack(AUnit* Attack, AUnit* Defense, const int32 side);

	void KillUnit(AUnit* Target);


	
	bool EnemyDamage(AUnit* Target);

	void MoveUnit(AUnit *Unit, const FIntPoint& EndCord, int32 side);

	void UnitAction(AUnit* Unit);
	/*
	void TimerFunction();
	FTimerHandle TimerHandle;
	int32 CallTracker = 2;
	*/


	// Sets default values for this actor's properties
	AGameplayManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;   // __ why virtual and override??

};
