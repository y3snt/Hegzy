// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Unreal Includes
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

// Gameplay
#include "GameplayEnums.h"

#include "HexGridManager.h"
#include "GridManager.h"
#include "Unit.h"

// Trick
#include "LevelUtils.h"
#include "Kismet/KismetMathLibrary.h"  // Max3 Function


#include "GameplayHandler.generated.h"

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
class HEKSY_API UGameplayHandler : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	

public:
	void helloworld();

	//UGameplayHandler();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;





protected:
	void SpawnUnits();

	int32 UnitsLeftToBeSummoned;

	EPlayer CurrentPlayer = EPlayer::ATTACKER;

	AUnit* SelectedUnit;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AutomaticTests|Basic")   // __ ? we can change the value of a blueprint later
	EAutomaticTestsList AutomaticTest;

	void SimpleAutomaticTests();
	bool SelectUnit(const FIntPoint& Cord);

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameplayProperties|Map")
	UGridManager* GridManager; 



	UPROPERTY(EditAnywhere, Category = "GameplayProperties|Map")
	TArray<TSubclassOf<AUnit>> AttackerUnitsTypes;

	UPROPERTY(EditAnywhere, Category = "GameplayProperties|Map")
	TArray<TSubclassOf<AUnit>> DefenderUnitTypes;


	TArray<AUnit*> AttackerUnits;
	TArray<AUnit*> DefenderUnit;

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


	void AttackUnit(AUnit* Target, int32 AttackSide);

	void Bow_Action(AUnit* Unit, int32 Side);

	void Spear_Action(AUnit* Unit, int32 Side);

	void Sword_Action(AUnit* Unit, int32 Side);

	void Push_Action(AUnit* Unit, int32 Side);
	/*
	void TimerFunction();
	FTimerHandle TimerHandle;
	int32 CallTracker = 2;
	*/


protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;   // __ why virtual and override??
};
