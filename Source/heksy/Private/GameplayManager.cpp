// Fill out your copyright notice in the Description page of Project Settings.

/**
 * Main Class of the Hegzy Project.
 * It generates neccesary values at the start of the level in BeginPlay()
 *  then await Input System to call "InputListerner(FIntPoint Cord)".
 * 
 * GameplayManager depends on the Unit.h and HexGridManager.h
 * //Unit - is the next layer of the architecture dealing with smaller and more detailed gameplay systems
 * GridManager - is a tool used to manage the map
 */


#include "GameplayManager.h"

#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::White, String)


#pragma region Tools

void AGameplayManager::SwitchPlayerTurn()
{ // Currently works only for 2 players
	CurrentPlayer = (CurrentPlayer == EPlayer::ATTACKER) ? EPlayer::DEFENDER : EPlayer::ATTACKER;
}

bool AGameplayManager::IsLegalMove(FIntPoint Cord, int32& ResultSide)
{
	/**
	 * Target Cord doesn't contatin an Enemy Unit with a shield pointing at our SelectedUnit
	 * 
	 * @param Cord
	 * @return true if selected Unit can move on a given Cord
	 */


	// Check if Cord is a neighbour of a SelectedUnit
	ResultSide = GridManager->AdjacentSide(SelectedUnit->CurrentCord, Cord);  
	if (ResultSide == INDEX_NONE)
		return false;

	// TODO: Check if SelectedUnit doesn't have push symbol on it's front (none currently have it yet)
	AUnit* EnemyUnit = GridManager->GetUnit(Cord);
	if (EnemyUnit == nullptr)  // Is there a Unit in this spot?
		return true;

	if (SelectedUnit->Symbols[0] == ESymbols::SHIELD)  // Can SelectedUnit kill EnemyUnit?
		return false;

	ESymbols EnemySymbol = EnemyUnit.GetSymbol(side + 3);
	if (EnemySymbol == ESymbols::SHIELD)  // Does EnemyUnit has a shield?
		return false;

	return true;
}



/* TODO
1 Action
2 Check for Spear Damage
3 Check for shield in IsLegalMove
*/


void AGameplayManager::MoveUnit(AUnit *Unit, const FIntPoint& EndCord, int32 side)
{ 
	// Move General function
	/**
	 * Move this unit to EndCord
	 *
	 * @param EndCord Position at which unit will be placed
	 */

	Unit->Rotate(side); // 1

	//TODO: if shields: // maybe check for every unit
	if (EnemyDamage(Unit))
	{
		KillUnit(Unit);
		return;
	}

	UnitAction(SelectedUnit);

	GridManager->ChangeUnitPosition(Unit, EndCord);

	if (EnemyDamage(Unit))
	{//spr czy nie giniemy HegzyEvents.OnUnitMoved(CurrentCord);
		KillUnit(Unit);
		return;
	}
		
	UnitAction(SelectedUnit);

}

bool AGameplayManager::SymbolAttack(AUnit* Attack, AUnit* Defense, const int32 side)
{
	return true;
}


bool AGameplayManager::EnemyDamage(AUnit* Target)
{ // Returns true is Enemy spear can kill the Target
	TArray<AUnit* > Units = GridManager->AdjacentUnits(Target->CurrentCord);

	for (int32 side = 0; side < 6; side++) 
	{	
		if (Units[side] != nullptr && Units[side]->Controller != Target->Controller)
		{

			ESymbols TargetSymbol = Target.GetSymbol(side);  // TODO: ew. check if !nullptr
			if (TargetSymbol == ESymbols::SHIELD)  // Do we have a shield?
				continue;
			
			Esymbols EnemySymbol = Units[side].GetSymbol(side + 3);  // TODO: ew. check if !nullptr
			if (EnemySymbol == ESymbols::SPEAR)  // Does enemy have a spear?
				return true;

		}
	}
	return false;
}

void AGameplayManager::KillUnit(AUnit* Target)
{
	if (Target->Controller == EPlayer::DEFENDER)
	{
		DefenderUnits.Remove(Target);
	}
	else
	{
		AttackerUnits.Remove(Target);
	}
	GridManager->RemoveUnit(Target);

	if (DefenderUnits.Num() == 0)
		PrintString("Attacker won");
	else if (AttackerUnits.Num() == 0)
		PrintString("Defender won");
	
}


void AGameplayManager::UnitAction(AUnit* Unit)
{
	TArray<AUnit* > Units = GridManager->AdjacentUnits(Unit->CurrentCord);

	for (int32 side = 0; side < 6; side++)
	{
		ESymbols UnitSymbol = Unit.GetSymbol(side);

		// BOW LOGIC
		if (UnitSymbol == ESymbols::BOW)
		{
			AUnit* Target = GridManager->GetShotTarget(Unit->CurrentCord, side);
			if (Target == nullptr || Target->Controller == Unit->Controller)
				continue;

			ESymbols EnemySymbol = Target->GetSymbol(side + 3);  // TODO: rename to ESymbol
			if (EnemySymbol != ESymbols::SHIELD) // Does Enemy has a shield?
				KillUnit(Target);

		}
		else if (Units[side] != nullptr && Units[side]->Controller != Unit->Controller)  // Enemy unit on the adjacent cord
		{
			AUnit EnemyUnit = Units[side];

			// PUSH LOGIC
			if (UnitSymbol == ESymbols::PUSH)
			{
				EHexTileType TargetTileType = GridManager->GetDistantTileType(Unit->CurrentCord, side, 2);
				AUnit* Target = GridManager->GetDistantUnit(Unit->CurrentCord, side, 2);

				if (TargetTileType == EHexTileType::SENTINEL || Target != nullptr)  // Pushing outside the map or in the Unit
				{
					KillUnit(EnemyUnit);
				}
				else if (Target == nullptr) // Simple push
				{
					GridManager->ChangeUnitPosition(EnemyUnit, GridManager->GetDistantCord(Unit->CurrentCord, side, 2));
					SpearDamage(EnemyUnit);
				}
				continue;
			}

			
			// ATTACK LOGIC (SPEAR OR SWORD)
			if (UnitSymbol == ESymbols::SHIELD || UnitSymbol == ESymbols::INVALID)  // Do we have a weapon?  TODO: if of type attackable / has tag ...
				continue;

			Esymbols EnemySymbol = EnemyUnit.GetSymbol(side + 3);
			if (EnemySymbol != ESymbols::SHIELD) // Does Enemy has a shield?
			{
				KillUnit(EnemyUnit);
			}

		}
	}

	/*
	for side in unit:
	 if side has symbol:
		szajs = symbol("active")
		if szajs not null
			mapa_jednsotek[szajs] = null
	

	symbol(mapa_jednostek):
		check if symbol is active:

	*/
}


#pragma endregion


#pragma region Main Functions


void AGameplayManager::InputListener(FIntPoint Cord)
{
	FString output = Cord.ToString();
	PrintString(output);

	if(SelectUnit(Cord) || SelectedUnit == nullptr) 
		return;


	if (UnitsLeftToBeSummoned > 0)  // Summon phase
	{
		/*
		* Units are placed by the players in subsequent order on their chosen "Starting Locations"
		* inside the area of the gameplay board.
		*/
		SummonUnit(Cord);
	}
	else  // Gameplay phase
	{
		Gameplay(Cord);
	}

	SelectedUnit = nullptr;  // IMPORTANT
}


bool SelectUnit(const FIntPoint& Cord) {
	/**
	 * Select friendly Unit on a given Cord
	 * 
	 * @return true if unit has been selected in this operation
	 */

	AUnit* NewSelection = GridManager->GetUnit(Cord);
	if (NewSelection != nullptr && NewSelection->Controller == CurrentPlayer)
	{
		SelectedUnit = NewSelection;
		PrintString("You have selected a Unit");

		return true;
	}

	return false;
}



void AGameplayManager::Gameplay(FIntPoint Cord)
{
	PrintString("Gameplay is working");

	int32 side;  // Gets Updated with IsLegalMove()
	if (IsLegalMove(Cord, side)) // spot is empty + we aren't hitting a shield
	{
		// 1 Rotate

		// 2 Check for Spear

		// 3 Actions

		// 4 Move

		// 5 Check for Spear

		// 6 Actions
		MoveUnit(SelectedUnit, Cord, side);
		//PrintString(FString::Printf(TEXT("DIRECTION_%d"), side));
		//testKillUnit(Cord);
		
		//GridManager->ChangeUnitPosition(SelectedUnit, Cord);
		//PrintString(FString::Printf(TEXT("_%d"), side));
		//->RotateUnit(SelectedUnit, side);

		SwitchPlayerTurn();
	}

}


void AGameplayManager::SummonUnit(FIntPoint Cord)
{
	/**
	 * Summon currently selected unit to a Gameplay Board
	 *
	 *
	 * @param Cord cordinate, on which Unit will be summoned
	 */
	

	// check if unit is already summoned
	EHexTileType SelectedUnitTileType = GridManager->GetTileType(SelectedUnit->CurrentCord);  // todo getters/setters

	if (SelectedUnitTileType != EHexTileType::SENTINEL)
	{
		PrintString("This Unit has been already summoned");
		return;
	}


	EHexTileType SelectedHexType = GridManager->GetTileType(Cord);

	bool bSelectedCurrentPlayerSpawn =
		(SelectedHexType == EHexTileType::ATTACKER_SPAWN && CurrentPlayer == EPlayer::ATTACKER) ||
		(SelectedHexType == EHexTileType::DEFENDER_SPAWN && CurrentPlayer == EPlayer::DEFENDER);

	if (!bSelectedCurrentPlayerSpawn)
	{
		PrintString("Thats a wrong summon location");  // TODO: Don't reset SelectedUnit
		return;
	}

	PrintString("You summoned a Unit");

	// TeleportUnit(Cord);
	GridManager->ChangeUnitPosition(SelectedUnit, Cord);

	if (CurrentPlayer == EPlayer::ATTACKER)  // TODO: Move to setup
		SelectedUnit->Rotate(0);
	else
		SelectedUnit->Rotate(3);


	SwitchPlayerTurn();

	UnitsLeftToBeSummoned--;
}
#pragma endregion

#pragma region Tests






void AGameplayManager::SimpleAutomaticTests()
{
	if (AutomaticTest == EAutomaticTestsList::EMPTY)
	{
		return;
	}


	if (AutomaticTest == EAutomaticTestsList::BASIC_UNIT_SETUP)
	{
		for (int32 i = 0; i < FMath::Max3(AttackerUnits.Num(), DefenderUnits.Num(), 0); i++)
		{
			if (i < AttackerUnits.Num())
			{
				InputListener(AttackerUnits[i]->CurrentCord);
				InputListener(AttackerUnits[i]->CurrentCord + AttackerUnits[i]->Direction(0));
			}
			if (i < DefenderUnits.Num())
			{
				InputListener(DefenderUnits[i]->CurrentCord);
				InputListener(DefenderUnits[i]->CurrentCord + DefenderUnits[i]->Direction(3));
			}
		}
		return;
	}
}
#pragma endregion



#pragma region GameSetup


void AGameplayManager::SpawnUnits()
{
	/*
	* Placing Units used in combat on their "Spawn Points" near the area of the gameplay board where they are visible to the players.
	*/

	UnitsLeftToBeSummoned = AttackerUnits.Num() + DefenderUnits.Num();  // Flag that manages the state of the game
	
	// spawning attacker units
	for (int32 i = 0; i < AttackerUnits.Num(); i++)
	{
		AttackerUnits[i]->Controller = EPlayer::ATTACKER;

		FIntPoint SpawnCord = GridManager->AttackerTiles[i]->TileIndex; // Get spawn location
		SpawnCord += AUnit::Direction(3);  // Move to a spot outside of the map near spawn point

		GridManager->ChangeUnitPosition(AttackerUnits[i], SpawnCord); // Adding Unit to the Gameplay Array
		
	}

	// spawning defender units
	for (int32 i = 0; i < DefenderUnits.Num(); i++)
	{
		DefenderUnits[i]->Controller = EPlayer::DEFENDER;

		FIntPoint SpawnCord = GridManager->DefenderTiles[i]->TileIndex; // Get spawn location
		SpawnCord += AUnit::Direction(0); // Move to a spot outside of the map near spawn point

		GridManager->ChangeUnitPosition(DefenderUnits[i], SpawnCord); // Adding Unit to the Gameplay Array
	}

	SelectedUnit = nullptr;
}


void AGameplayManager::SetupGame()
{
	GridManager->GenerateGrid();
	SpawnUnits();

	//GetWorldTimerManager().SetTimer(TimerHandle, this, &AGameplayManager::TimerFunction, 1.0f, true, 0.5f);
	SimpleAutomaticTests();
}

/*
void AGameplayManager::TimerFunction()
{
	CallTracker--;
	if (CallTracker == 0)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		SimpleAutomaticTests();
	}
}
*/

void AGameplayManager::BeginPlay()
{
	SetupGame();
}


AGameplayManager::AGameplayManager()
{
	AutomaticTest = EAutomaticTestsList::EMPTY;
}

#pragma endregion