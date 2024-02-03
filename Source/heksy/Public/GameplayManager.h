/**
 * Main Class of the Hegzy Project, which manages whole gameplay
 * It awaits Input System to call "InputListerner(Cord)".
 * and selects/moves/summons Units, based on a selected cord
 */

#pragma once

// Unreal Includes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelUtils.h"
#include "Kismet/KismetMathLibrary.h"  // Max3 Function

// Gameplay Actor
#include "HexGridManager.h"
#include "Unit.h"
#include "GameplayEnums.h"

#include "GameplayManager.generated.h"


UCLASS()
class HEKSY_API AGameplayManager : public AActor
{
	GENERATED_BODY()

protected:
	static int32 UnitsLeftToBeSummoned;  // Flag that manages the state of the game
	static EPlayer CurrentPlayer;
	static AUnit* SelectedUnit;
	static int32 AttackerUnitsAlive;
	static int32 DefenderUnitsAlive;
	
	/* Called before BeginPlay */
	virtual void PostInitializeComponents() override; 

	/* Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	static void Gameplay(FIntPoint Cord);
	static void SwitchPlayerTurn();

	/**
	 * Select an ally Unit on a given Cord
	 * 
	 * @return true if unit has been selected in this operation
	 */
	static bool SelectUnit(const FIntPoint& Cord);

	/**
	 * Summon currently selected unit to a Gameplay Board
	 *
	 * @param Cord cordinate, on which Unit will be summoned
	 */
	static void SummonUnit(FIntPoint Cord);

	/**
	 * Check if Game ends
	 */
	static void CheckWin();

public:
	AGameplayManager();

	/**
	 * Initialize values of a GameplayManager
	 */
	static void GameSetup();

	/**
	 * Perfroms actions with Units, based on a Player mouse input
	 * 
	 * @param Cord on which Player has selected
	 */
	static void InputListener(FIntPoint Cord);

	/**
	 * Check if SelectedUnit can move to a given cord
	 * 
	 * @param Cord
	 * @return true if selected Unit can move on a given Cord
	 * @note If a Cord is adjacent, ajdacent side will be assigned in ResultSide
	 */
	static bool IsLegalMove(FIntPoint Cord, int32& ResultSide);

	/**
	 * Remove Target Unit from a Game, update Game variables
	 * 
	 * @param Target Unit to remove
	 */
	static void KillUnit(AUnit* Target);
	
	/**
	 * Invokes Passive Actions of Enemy Units, adjacent to Target
	 * 
	 * @param Target Unit on which Passive Action will be performed
	 * @note Target may be killed during this operation
	 */
	static void EnemyDamage(AUnit* Target);

	/**
	 * Move Selected Unit to EndCord
	 * 
	 * @param EndCord Position at which unit will be placed
	 * @param int32 Side
	 */
	static void MoveUnit(const FIntPoint& EndCord, int32 Side);
};
