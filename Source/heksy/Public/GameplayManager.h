/**
 * Main Class of the Hegzy Project.
 * It generates neccesary values at the start of the level in BeginPlay()
 *  then await Input System to call "InputListerner(FIntPoint Cord)".
 * 
 * GameplayManager depends on the Unit.h and HexGridManager.h
 * //Unit - is the next layer of the architecture dealing with smaller and more detailed gameplay systems
 * GridManager - is a tool used to manage the map
 */

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


UCLASS()
class HEKSY_API AGameplayManager : public AActor
{
	GENERATED_BODY()

protected:
	static int32 UnitsLeftToBeSummoned;
	static EPlayer CurrentPlayer;
	static AUnit* SelectedUnit;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override; 

	static bool SelectUnit(const FIntPoint& Cord);

	static void CheckWin();

public:  // TODO: why all of those are public
	static int32 AttackerUnitsAlive;
	static int32 DefenderUnitsAlive;

	AGameplayManager();

	static void GameSetup();

	static void InputListener(FIntPoint Cord);

	static void SummonUnit(FIntPoint Cord);

	static void SetupGame();

	static void SwitchPlayerTurn();

	static void Gameplay(FIntPoint Cord);

	/**
	 * Check if SelectedUnit can move to a given cord
	 * 
	 * @param Cord
	 * @return true if selected Unit can move on a given Cord
	 * @note If a Cord is adjacent, ajdacent side will be assigned in ResultSide
	 */
	static bool IsLegalMove(FIntPoint Cord, int32& ResultSide);

	static void KillUnit(AUnit* Target);
	
	static void EnemyDamage(AUnit* Target);

	/**
	* Move Selected Unit to EndCord
	* 
	* @param EndCord Position at which unit will be placed
	* @param int32 Side
	*/
	static void MoveUnit(const FIntPoint& EndCord, int32 Side);
};
