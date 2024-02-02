// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// Basic Includes
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
	static int32 UnitsLeftToBeSummoned;
	static EPlayer CurrentPlayer;
	static AUnit* SelectedUnit;

	UPROPERTY(EditAnywhere, Category = "AutomaticTests|Basic")
	EAutomaticTestsList UAutomaticTest;
	
	static EAutomaticTestsList AutomaticTest;

	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override; 

	static void SimpleAutomaticTests();

	static bool SelectUnit(const FIntPoint& Cord);

	static void CheckWin();

public:  // TODO: why all of those are public
	UPROPERTY(EditAnywhere, Category = "GameplayProperties|Map")
	int32 UAttackerUnitsAlive;
	static int32 AttackerUnitsAlive;
	
	UPROPERTY(EditAnywhere, Category = "GameplayProperties|Map")
	int32 UDefenderUnitsAlive;
	static int32 DefenderUnitsAlive;

	AGameplayManager();

	static void InputListener(FIntPoint Cord);

	static void SummonUnit(FIntPoint Cord);

	static void SetupGame();

	static void SwitchPlayerTurn();

	static void Gameplay(FIntPoint Cord);

	static bool IsLegalMove(FIntPoint Cord, int32& ResultSide);

	static void KillUnit(AUnit* Target);
	
	static void EnemyDamage(AUnit* Target);

	static void MoveUnit(const FIntPoint& EndCord, int32 side);
};
