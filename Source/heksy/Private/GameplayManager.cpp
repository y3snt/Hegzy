// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayManager.h"

#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, String)



AGameplayManager::AGameplayManager()
{

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
		SummonUnit(Cord);
	}
	else  // Gameplay phase
	{
		Gameplay(Cord);
	}

	SelectedUnit = nullptr;  // IMPORTANT
}



/**
 * Summon currently selected unit to a Gameplay Board
 * 
 * @param Cord cordinate, on which Unit will be summoned
 */
void AGameplayManager::SummonUnit(FIntPoint Cord)
{
	/*
	* Placing Units by the player in subsequent order on their chosen "Starting Locations"
	* inside the area of the gameplay board.
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
	SwitchPlayerTurn();

	UnitsLeftToBeSummoned--;
}




void AGameplayManager::SwitchPlayerTurn()
{
	CurrentPlayer = (CurrentPlayer == EPlayer::ATTACKER) ? EPlayer::DEFENDER : EPlayer::ATTACKER;
}


void AGameplayManager::Gameplay(FIntPoint Cord)
{
	PrintString("Gameplay is working");
}


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

}


/*


void AGameplayManager::TimerFunction()
{
	CallTracker--;
	if (CallTracker == 0)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		SetupGame();
	}
}
*/

void AGameplayManager::BeginPlay()
{
	SetupGame();
	
	//GetWorldTimerManager().SetTimer(TimerHandle, this, &AGameplayManager::TimerFunction, 1.0f, true, 0.5f);
	
}