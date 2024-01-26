﻿// Fill out your copyright notice in the Description page of Project Settings.

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

#include "GlobalEvents.h"

#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::White, String)

class ASymbol;




#pragma region Tools

void AGameplayManager::SwitchPlayerTurn()
{ // Currently works only for 2 players
	CurrentPlayer = (CurrentPlayer == EPlayer::ATTACKER) ? EPlayer::DEFENDER : EPlayer::ATTACKER;
}

bool AGameplayManager::IsLegalMove(FIntPoint Cord, int32& ResultSide)
{
	/**
	 Function checks 2 things:
	 * 1 Target Cord is a Neighbour of a SelectedUnit
	 * 2 If SelectedUnit doesn't have push symbol on it's front (none currently have it yet)
	 *	 Target Cord doesn't contatin an Enemy Unit with a shield pointing at our SelectedUnit
	 */

	// 1
	ResultSide = GridManager->AdjacentSide(SelectedUnit->CurrentCord, Cord);  
	if (ResultSide == INDEX_NONE)
		return false;

	// 2
	AUnit* EnemyUnit = GridManager->GetUnit(Cord);
	if (EnemyUnit == nullptr)  // Is there a Unit in this spot?
		return true;

	// checking if can attack from the front, cause SelectedUnit will rotate first
	if (!SelectedUnit->CanAttack() || EnemyUnit->CanDefend(ResultSide + 3, SelectedUnit->GetFrontSymbol()))
		return false;

	return true;
}


	

// TODO: invoke Move Events!!!
void AGameplayManager::MoveUnit(AUnit *Unit, const FIntPoint& EndCord, int32 side)
{ 
	/**  General Move function
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
	//TODO wait half a second


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

// TODO: subscribe to UnitMoved Event !!! and Kill Unit
bool AGameplayManager::EnemyDamage(AUnit* Target)
{ // Returns true is Enemy spear can kill the Target
	TArray<AUnit* > Units = GridManager->AdjacentUnits(Target->CurrentCord);

	for (int32 side = 0; side < 6; side++)
	{	
		if (Units[side] != nullptr && Units[side]->Controller != Target->Controller)
		{
			// TODO: ew. check if target !nullptr
			if(Target->CanDefend(side)) 
				continue;

			// TODO: perform passive action 
			if (Units[side]->GetSymbol(side + 3) == ESymbols::SPEAR) // Does enemy has a spear?
			{
				return true;
			}
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
	// GridManager->RemoveUnit(Target); -- activated on Death Event

	// TODO: Not here!  ? decorators
	if (DefenderUnits.Num() == 0)
		PrintString("Attacker won");
	else if (AttackerUnits.Num() == 0)
		PrintString("Defender won");
	
}


void AGameplayManager::UnitAction(AUnit* Unit)
{
	//TArray<AUnit* > Units = GridManager->AdjacentUnits(Unit->CurrentCord);

	for (int32 side = 0; side < 6; side++)
	{
		ESymbols UnitSymbol = Unit->GetSymbol(side);
		
		switch (UnitSymbol)
		{
			case ESymbols::BOW:
			{
				Bow_Action(Unit, side);
				break;
			}
			
	
			case ESymbols::PUSH:
			{
				Push_Action(Unit, side);
				break;
			}

			case ESymbols::SPEAR:// Enemy unit on the adjacent cord
			case ESymbols::SWORD:
			{
				Spear_Action(Unit, side);
				break;
			}
		}
		


		/*
		switch (UnitWeapon)
		{
			case ESymbols::INVALID: 
			case ESymbols::SHIELD:
				break; // We don't have a weapon

			case ESymbols::BOW:
			{
				AUnit* Target = GridManager->GetShotTarget(Unit->CurrentCord, side);
				if (Target == nullptr)
					break;

				if (Target->Controller == Unit->Controller)
					break;


				if (Target->GetSymbol(side + 3) != ESymbols::SHIELD) // Does Enemy has a shield?
				{
					KillUnit(Target);
				}
				break;
			}
			
			default:
			{
				if (Units[side] == nullptr || Units[side]->Controller == Unit->Controller)
				{ // no one to hit
					break;
				}

				AUnit* EnemyUnit = Units[side];

				if (UnitWeapon == ESymbols::PUSH)
				{
					// PUSH LOGIC
					EHexTileType TargetTileType = GridManager->GetDistantTileType(Unit->CurrentCord, side, 2);

					if (TargetTileType == EHexTileType::SENTINEL)  // Pushing outside the map
					{
						// Kill
						KillUnit(EnemyUnit);
						break;
					}


					AUnit* Target = GridManager->GetDistantUnit(Unit->CurrentCord, side, 2);

					if (Target != nullptr) // Spot isn't empty
					{
						KillUnit(EnemyUnit);
						break;
					}

					GridManager->ChangeUnitPosition(EnemyUnit, GridManager->GetDistantCord(Unit->CurrentCord, side, 2));
					if (EnemyDamage(EnemyUnit)) // Simple push	
					{
						KillUnit(EnemyUnit);
					}
					break;
				}


				// Rotation is based on where the unit is pointing toward


				if (EnemyUnit->GetSymbol(side + 3) != ESymbols::SHIELD) // Does Enemy has a shield?
				{
					KillUnit(Units[side]);
				}
				
			}
		}
		*/
	}
}

AUnit* AGameplayManager::GetAdjacentEnemy(const AUnit* Unit, int32 Side)
{
	AUnit* Target = GridManager->GetUnit(
		GridManager->AdjacentCord(
		Unit->CurrentCord, Side));

	if(Target && Target->Controller != Unit->Controller)
		return Target;

	return nullptr;
}

void AGameplayManager::Bow_Action(AUnit* Unit, int32 Side)
{
	AUnit* Target = GridManager->GetShotTarget(Unit->CurrentCord, Side);
	if (Target && Target->Controller != Unit->Controller)
		Target->TakeDamage(Side);
}

// Adjacent Attack
void AGameplayManager::Spear_Action(AUnit* Unit, int32 Side)
{
	AUnit* Target = GetAdjacentEnemy(Unit, Side);
	if (Target)
		Target->TakeDamage(Side);
}

void AGameplayManager::Sword_Action(AUnit* Unit, int32 Side)
{
	AUnit* Target = GetAdjacentEnemy(Unit, Side);
	if (Target)
		Target->TakeDamage(Side);
}

void AGameplayManager::Push_Action(AUnit* Unit, int32 Side)
{
	AUnit* Target = GetAdjacentEnemy(Unit, Side);
	if (!Target)
		return;

	EHexTileType BehindTile = GridManager->GetDistantTileType(Unit->CurrentCord, Side, 2);
	AUnit* BehindUnit = GridManager->GetDistantUnit(Unit->CurrentCord, Side, 2);

	// TODO: Move to hex grid MG (which will validate position and kill if on a bad position)
	if (BehindUnit != nullptr || BehindTile == EHexTileType::SENTINEL)  // Pushing outside the map or in the Unit
	{
		KillUnit(Target);
	}
	else if (BehindUnit == nullptr) // Simple push TODO: we don't need else if here, just else
	{
		GridManager->ChangeUnitPosition(Target, GridManager->GetDistantCord(Unit->CurrentCord, Side, 2));
		if (EnemyDamage(Target))  // TODO: should be passive
			KillUnit(Target);
	}
}

bool AGameplayManager::SelectUnit(const FIntPoint& Cord) {
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

#pragma endregion


#pragma region Main Functions


void AGameplayManager::InputListener(FIntPoint Cord)
{
	FString output = Cord.ToString();
	PrintString(output);

	if (SelectUnit(Cord) || SelectedUnit == nullptr)
		return; // selected a new unit || wrong input which didn't select any ally unit



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

	if (CurrentPlayer == EPlayer::ATTACKER)
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
	
	
	//SimpleAutomaticTests();
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
	//GlobalEvents::OnUnitDeath += KillUnit;
	SetupGame();
}


AGameplayManager::AGameplayManager()
{
	AutomaticTest = EAutomaticTestsList::EMPTY;
}

#pragma endregion