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
	int32 UnitsLeftToBeSummoned;
	EPlayer CurrentPlayer = EPlayer::ATTACKER;
	static AUnit* SelectedUnit;

	UPROPERTY(EditAnywhere, Category = "AutomaticTests|Basic")
	EAutomaticTestsList AutomaticTest;

	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override; 

	void SpawnUnits();

	void SimpleAutomaticTests();

	bool SelectUnit(const FIntPoint& Cord);

	static void CheckWin();

public:  // TODO: why all of those are public
	UPROPERTY(EditAnywhere, Category = "GameplayProperties|Map")
	TArray<AUnit*> UAttackerUnits;
	static TArray<AUnit*> AttackerUnits;
	
	UPROPERTY(EditAnywhere, Category = "GameplayProperties|Map")
	TArray<AUnit*> UDefenderUnits;
	static TArray<AUnit*> DefenderUnits;

	AGameplayManager();

	void InputListener(FIntPoint Cord);

	void SummonUnit(FIntPoint Cord);

	void SetupGame();

	void SwitchPlayerTurn();

	void Gameplay(FIntPoint Cord);

	bool IsLegalMove(FIntPoint Cord, int32& ResultSide);

	static void KillUnit(AUnit* Target);
	
	static void EnemyDamage(AUnit* Target);

	void MoveUnit(const FIntPoint& EndCord, int32 side);
};
