// Fill out your copyright notice in the Description page of Project Settings.

#include "HexGridManager.h"


const TArray<FIntPoint> AHexGridManager::Directions = {
	FIntPoint(1, 0),
	FIntPoint(0, 1),
	FIntPoint(-1, 1),
	FIntPoint(-1, 0),
	FIntPoint(0, -1),
	FIntPoint(1, -1)
};



EHexTileType AHexGridManager::GetTileType(const FIntPoint& Cord) const
{
	return HexGrid[Cord.X][Cord.Y]->TileType;
}

AUnit* AHexGridManager::GetUnit(const FIntPoint& Cord)
{
	return UnitGrid[Cord.X][Cord.Y];
}

void AHexGridManager::ChangeUnitPosition(AUnit *Unit, const FIntPoint& Cord)
{
	UnitGrid[Unit->CurrentCord.X][Unit->CurrentCord.Y] = nullptr; // clean your previous location
	UnitGrid[Cord.X][Cord.Y] = Unit; // UnitGrid Update

	Unit->CurrentCord = Cord; // update Unit Index
	
	Unit->SetActorLocation(HexGrid[Cord.X][Cord.Y]->GetActorLocation()); // Move visuals of the unit
}

void AHexGridManager::RotateUnit(AUnit* Unit, int32 Direction)
{
	/**
	 * 360 / 6 = 60 -> degrees needed to rotate unit
	 *
	 * \param Unit - Reference to the object we are rotating
	 */
	Unit->CurrentRotation = Direction;
	// "Direction + 4" Accounts for global rotation setting for objects in the level
	Unit->SetActorRotation(FRotator(0, 60 * (Direction + 4), 0), ETeleportType::TeleportPhysics);
}



void AHexGridManager::RemoveUnit(AUnit* Unit)
{
	FIntPoint Cord = Unit->CurrentCord;
	UnitGrid[Cord.X][Cord.Y] = nullptr; // Remove unit from gameplay grid

	//Unit->SetActorLocation(HexGrid[0][0]->GetActorLocation());
	//Unit->Destroy();
}

#pragma region Coordinates tools

TArray<AUnit*> AHexGridManager::AdjacentUnits(const FIntPoint& BaseCord)
{ // Returns 6 elements Array, elements can be nullptr
	TArray<AUnit* > Units;
	for (int side = 0; side < 6; side++)
	{
		FIntPoint Cord = AdjacentCord(BaseCord, side);
		AUnit* Neighbour = UnitGrid[Cord.X][Cord.Y];
		//if (Neighbour != nullptr)
		Units.Add(Neighbour);
	}
	return Units;
}

AUnit* AHexGridManager::GetShotTarget(FIntPoint StartCord, const int32 Side)
{
	while (HexGrid[StartCord.X][StartCord.Y]->TileType != EHexTileType::SENTINEL)
	{
		StartCord += Directions[Side];
		AUnit* Target = UnitGrid[StartCord.X][StartCord.Y];
		if (Target != nullptr)
			return Target;
	} 
	return nullptr;
}

AUnit* AHexGridManager::GetDistantUnit(FIntPoint StartCord, const int32 Side, const int32 Distance)
{
	for (int32 i = 0; i < Distance; i++)
	{
		StartCord += Directions[Side];
	}
	return UnitGrid[StartCord.X][StartCord.Y];
}

EHexTileType AHexGridManager::GetDistantTileType(FIntPoint StartCord, const int32 Side, const int32 Distance)
{
	for (int32 i = 0; i < Distance; i++)
	{
		StartCord += Directions[Side];
	}
	return HexGrid[StartCord.X][StartCord.Y]->TileType;
}

FIntPoint AHexGridManager::GetDistantCord(FIntPoint& StartCord, const int32 Side, const int32 Distance)
{
	FIntPoint NewCord = StartCord;
	for (int32 i = 0; i < Distance; i++)
	{
		NewCord += Directions[Side];
	}
	return NewCord;
}



bool AHexGridManager::IsAdjacent(const FIntPoint& Cord1, const FIntPoint& Cord2)
{
	int32 Index = Directions.Find(Cord2 - Cord1);

	return (Index == INDEX_NONE)? false : true;
}

int32 AHexGridManager::AdjacentSide(const FIntPoint& Cord1, const FIntPoint& Cord2)
{	
	/**
	* Return shared side between Cord1 and Cord2, if Cords are adjacent
	* 
	* @param Cord1 
	* @param Cord2 
	* @return int32 Side number | INDEX_NONE 
	* @note INDEX_NONE is returned, when Cord1 and Cord2 don't have shared side
	*/
	return Directions.Find(Cord2 - Cord1);
}


FIntPoint AHexGridManager::AdjacentCord(const FIntPoint& BaseCord, int32 Side)
{
	/**
	 * Return cord adjacent to BaseCord at given Side
	 *
	 * @param BaseCord
	 * @param Side {0, 1, ..., 5}
	 * @return FIntPoint Cord adjacent to BaseCord
	 */
	return BaseCord + Directions[Side];
}

/* Maybe TODO
FIntPoint AHexGridManager::AdjacentCord(const FIntPoint& BaseCord, const FIntPoint& Direction)
{
	/**
	 * Return cord adjacent to BaseCord at given Direction
	 *
	 * @param BaseCord
	 * @param Side {0, 1, ..., 5}
	 * @return FIntPoint Cord adjacent to BaseCord
	 */
	// TODO: Normalize dircetion first to match one of the Directions
	//return BaseCord + Directions[Side];
//}

#pragma endregion

#pragma region GenerateGrid

void AHexGridManager::BlueprintsCheck()
{
	checkf(AttackerHexTile != NULL, TEXT("no AttackerHexTile"));
	checkf(DefaultHexTile != NULL, TEXT("no DefaultHexTile"));
	checkf(DefenderHexTile != NULL, TEXT("no DefenderHexTile"));
	checkf(SentinelHexTile != NULL, TEXT("no SentinelHexTile"));	
}

void AHexGridManager::AdjustGridSize()
{	
	// sentinels appear on both sides
	GridWidth += BorderSize * 2;
	GridHeight += BorderSize * 2;
	GridWidth += floor(GridHeight / 2);  // adjustment for Axial grid system

}

//#include <typeinfo>

void AHexGridManager::InitHexGridArray() 
{

	HexGrid.SetNumZeroed(GridWidth);  // __ how it works exactly - print the content / debugger
	UnitGrid.SetNumZeroed(GridWidth);

	//auto x = typeid(HexGrid2DArray[0]).name();
	//FString::Printf(x);

	//if (UnitGrid2DArray[0] == std::nullptr_t)
	

	for (int32 i = 0; i < HexGrid.Num(); i++)
	{
		UnitGrid[i].SetNumZeroed(GridHeight);
		HexGrid[i].SetNumZeroed(GridHeight);  
	}
}

void AHexGridManager::SpawnTiles()
{
	for (int32 y = 0; y < GridHeight; y++)
	{
		for (int32 x = 0; x < GridWidth; x++)
		{
			const bool oddRow = y % 2 == 0;  // Sentinel Rows add aditional row
			
			const float XTilePos = x * TileHorizontalOffset + y * OddRowHorizontalOffset;
			const float YTilePos = y * TileVerticalOffset;

			AHexTile* newTile = GetWorld()->SpawnActor<AHexTile>(GetTileToSpawn(x, y, oddRow),
																	FVector(FIntPoint(XTilePos, YTilePos)),
																	FRotator::ZeroRotator);
			newTile->TileIndex = FIntPoint(x, y);
			
			if (current_spawn == EHexTileType::SENTINEL)
			{	
				//newTile->SetActorLabel(FString::Printf(TEXT("Tile_Sentinel_%d-%d"), x, y));
			}
			else if (current_spawn == EHexTileType::DEFAULT)
			{
				//newTile->SetActorLabel(FString::Printf(TEXT("Tile_Default_%d-%d"), x, y));
			}
			else if (current_spawn == EHexTileType::ATTACKER_SPAWN)
			{
				//newTile->SetActorLabel(FString::Printf(TEXT("Tile_Attacker_Spawn_%d-%d"), x, y));
				AttackerTiles.Add(newTile);
			}
			else if (current_spawn == EHexTileType::DEFENDER_SPAWN)
			{
				//newTile->SetActorLabel(FString::Printf(TEXT("Tile_Defender_Spawn_%d-%d"), x, y));
				DefenderTiles.Add(newTile);
			}

			newTile->TileType = current_spawn;

			HexGrid[x][y] = newTile;
		}

	}
}

bool AHexGridManager::isGameplayTile(const int32 x, const int32 y, bool bOddRow)
{
	/*
	3:1 - 7:1 even 5
	3:2 - 6:2 odd 4
	2:3 - 6:3 even 5
	2:4 - 5:4 odd 4
	1:5 - 6:5 even 5

	
	*/
	int32 start = floor(GridHeight / 2); // axial start position
	int32 gameplay_width_start = start + BorderSize - floor(y / 2);
	int32 gameplay_height_start = BorderSize;

	int32 gameplay_height_end = GridHeight - BorderSize;
	int32 gameplay_width_odd_end = GridWidth - BorderSize - floor(y / 2);
	int32 gameplay_width_even_end = GridWidth - BorderSize - floor(y / 2);


	return (gameplay_height_start	  <= y && y < gameplay_height_end)					// Height
		&& ((gameplay_width_start	  <= x && x < gameplay_width_even_end && !bOddRow)  // even row width
		|| ( gameplay_width_start + 1 <= x && x < gameplay_width_odd_end  && bOddRow)); // odd row width

}

TSubclassOf<AHexTile> AHexGridManager::GetTileToSpawn(const int32 x, const int32 y, bool bOddRow)
{
	TSubclassOf<AHexTile> TileToSpawn = SentinelHexTile;  // Default value for hex tile is Sentinel Tile
	current_spawn = EHexTileType::SENTINEL;

	if (isGameplayTile(x, y, bOddRow))
	{
		TileToSpawn = DefaultHexTile;
		current_spawn = EHexTileType::DEFAULT;

		int32 FirstColumnStart = floor(GridHeight / 2) + BorderSize - floor(y / 2);
		if (bOddRow ? x == FirstColumnStart + 1 : x == FirstColumnStart) // first column
		{
			TileToSpawn = AttackerHexTile;
			current_spawn = EHexTileType::ATTACKER_SPAWN;
		}
		else if (x == GridWidth - BorderSize - 1  - floor(y / 2)) // last column
		{
			TileToSpawn = DefenderHexTile;
			current_spawn = EHexTileType::DEFENDER_SPAWN;
			
		}
	}
	


	return TileToSpawn;
}


// Called when the game starts or when spawned
void AHexGridManager::GenerateGrid()
{
	BlueprintsCheck();

	// "+2" is to reserve space for sentinel tiles on each side of the board
	AdjustGridSize();

	InitHexGridArray();
	SpawnTiles();

}

void AHexGridManager::BeginPlay()
{
	//GenerateGrid();
}

// Sets default values
AHexGridManager::AHexGridManager()
{
	GridWidth = 5;
	GridHeight = 5;

	BorderSize = 1;
}




#pragma endregion


