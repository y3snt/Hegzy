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

	AUnit* NewSelection = IsThereAllyUnit(Cord);
	if (NewSelection != nullptr)
	{
		SelectedUnit = NewSelection;
		PrintString("You have selected a Unit");
		
		return;
	}
	else if (SelectedUnit == nullptr)
	{
		return;
	}


	if (UnitsLeftToBeSummoned > 0)
	{
		SummonUnit(Cord);
	}
	else
	{
		Gameplay(Cord);
	}

	SelectedUnit = nullptr;  // IMPORTANT
}

AUnit* AGameplayManager::IsThereAllyUnit(FIntPoint Cord)
{
	AUnit* Target = GridManager->UnitGrid2DArray[Cord.X][Cord.Y];

	/*
	for (int i = 0; i < GridManager->UnitGrid2DArray.Num(); i++)
	{
		for (int j = 0; j < GridManager->UnitGrid2DArray[0].Num(); j++)
		{
			if (GridManager->UnitGrid2DArray[i][j] != nullptr)
			{
				if (GEngine) // prints stuff to screen
					GEngine->AddOnScreenDebugMessage(-1, 15.0f,
						FColor::Yellow, FString::Printf(TEXT("Units_%d_%d"), i, j), true);
			}
		}
	}
	*/

	
	


	if (Target != nullptr && Target->Owner == CurrentPlayer)
	{
		return Target;
	}
		

	return nullptr;
}


void AGameplayManager::SummonUnit(FIntPoint Cord)
{
	/*
	* Placing Units by the player in subsequent order on their chosen "Starting Locations"
	* inside the area of the gameplay board.
	*/
	if (GridManager->HexGrid2DArray[SelectedUnit->TileIndex.X][SelectedUnit->TileIndex.Y]->TileType != EHexTileType::SENTINEL)
	{
		PrintString("This Unit has been already summoned");
		return;
	}


	if (GEngine) // prints stuff to screen
		GEngine->AddOnScreenDebugMessage(-1, 15.0f,
			FColor::Yellow, FString::Printf(TEXT("You summon a Unit")), true);
	
	EHexTileType SelectedHex = GridManager->HexGrid2DArray[Cord.X][Cord.Y]->TileType;

	
	if ((SelectedHex != EHexTileType::ATTACKER || CurrentPlayer != EPlayer::ATTACKER) &&
		(SelectedHex != EHexTileType::DEFENDER || CurrentPlayer != EPlayer::DEFENDER))
	{
		if (GEngine) // prints stuff to screen
			GEngine->AddOnScreenDebugMessage(-1, 15.0f,
				FColor::Yellow, FString::Printf(TEXT("Thats a wrong summon location")), true);
		return;
	}
	
	TeleportUnit(Cord);
	SwitchPlayerTurn();

	UnitsLeftToBeSummoned -= 1;
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

	// Asserting correct map settings
	if (AttackerUnits.Num() > GridManager->AttackerTiles.Num() || DefenderUnits.Num() > GridManager->DefenderTiles.Num())
	{
		if (GEngine) // prints stuff to screen
			GEngine->AddOnScreenDebugMessage(-1, 15.0f,
				FColor::Yellow, FString::Printf(TEXT("AGameplayManager::SpawnUnits() Board is too small for that number of units")), true);
		return;
	}


	UnitsLeftToBeSummoned = AttackerUnits.Num() + DefenderUnits.Num();  // Flag that manages the state of the game


	// spawning attacker units
	for (int32 i = 0; i < AttackerUnits.Num(); i++)
	{
		SelectedUnit = AttackerUnits[i];
		SelectedUnit->Owner = EPlayer::ATTACKER;

		FIntPoint TI = GridManager->AttackerTiles[i]->TileIndex; // Get spawn location
		TI += AttackerUnits[i]->Neighbours(3);  // Move to a spot outside of the map near spawn point


		GridManager->UnitGrid2DArray[TI.X][TI.Y] = SelectedUnit; // Adding Unit to the Gameplay Array
		TeleportUnit(TI);
	}
	// spawning defender units
	for (int32 i = 0; i < DefenderUnits.Num(); i++)
	{
		SelectedUnit = DefenderUnits[i];
		SelectedUnit->Owner = EPlayer::DEFENDER;

		FIntPoint TI = GridManager->DefenderTiles[i]->TileIndex; // Get spawn location
		TI += SelectedUnit->Neighbours(0); // Move to a spot outside of the map near spawn point

		
		GridManager->UnitGrid2DArray[TI.X][TI.Y] = SelectedUnit; // Adding Unit to the Gameplay Array
		TeleportUnit(TI);
	}

	SelectedUnit = nullptr;
}


void AGameplayManager::TeleportUnit(FIntPoint Cord)
{
	GridManager->UnitGrid2DArray[SelectedUnit->TileIndex.X][SelectedUnit->TileIndex.Y] = nullptr;
	GridManager->UnitGrid2DArray[Cord.X][Cord.Y] = SelectedUnit; // UnitGrid Update

	SelectedUnit->TileIndex = Cord; // update Unit Index
	

	SelectedUnit->SetActorLocation(GridManager->HexGrid2DArray[Cord.X][Cord.Y]->GetActorLocation()); // Move visuals of the unit
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