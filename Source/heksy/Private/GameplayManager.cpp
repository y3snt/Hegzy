// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayManager.h"

#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, String)



AGameplayManager::AGameplayManager()
{
	AutomaticTest = EAutomaticTestsList::EMPTY;
}


void AGameplayManager::InputListener(FIntPoint Cord)
{
	FString output = Cord.ToString();
	PrintString(output);

	AUnit* NewSelection = GridManager->GetUnit(Cord);
	if (NewSelection != nullptr && NewSelection->Controller == CurrentPlayer)
	{
		SelectedUnit = NewSelection;
		PrintString("You have selected a Unit");
		
		return;
	}
	else if (SelectedUnit == nullptr)
	{
		return;
	}


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





void AGameplayManager::SwitchPlayerTurn()
{
	CurrentPlayer = (CurrentPlayer == EPlayer::ATTACKER) ? EPlayer::DEFENDER : EPlayer::ATTACKER;
}


void AGameplayManager::Gameplay(FIntPoint Cord)
{
	PrintString("Gameplay is working");
	testKillUnit(Cord);
}


void AGameplayManager::testKillUnit(FIntPoint Cord)
{
	AUnit* NewSelection = GridManager->GetUnit(Cord);
	if (NewSelection != nullptr && NewSelection->Controller != CurrentPlayer)
	{
		if (CurrentPlayer == EPlayer::DEFENDER)
		{
			AttackerUnits.Remove(NewSelection);
		}
		else
		{
			DefenderUnits.Remove(NewSelection);
		}
		GridManager->RemoveUnit(NewSelection, Cord);

		if (CurrentPlayer == EPlayer::ATTACKER && DefenderUnits.Num() == 0)
			PrintString("Attacker won");
		else if(CurrentPlayer == EPlayer::DEFENDER && AttackerUnits.Num() == 0)
			PrintString("Defender won");

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
		GridManager->RotateUnit(SelectedUnit, 4);
	else
		GridManager->RotateUnit(SelectedUnit, 1);
	SwitchPlayerTurn();

	UnitsLeftToBeSummoned--;
}

#include "Kismet/KismetMathLibrary.h"
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

#pragma endregion