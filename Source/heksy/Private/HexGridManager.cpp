// Fill out your copyright notice in the Description page of Project Settings.

#include "HexGridManager.h"
#include "GameplayManager.h"

// static members declaration
const TArray<FIntPoint> AHexGridManager::Directions = 
{  // order is important
	FIntPoint(1, 0),
	FIntPoint(0, 1),
	FIntPoint(-1, 1),
	FIntPoint(-1, 0),
	FIntPoint(0, -1),
	FIntPoint(1, -1)
};

EHexTileType AHexGridManager::current_spawn = EHexTileType::SENTINEL;

TArray<TArray<AHexTile *>> AHexGridManager::HexGrid;

int32 AHexGridManager::GridWidth;
int32 AHexGridManager::GridHeight;
int32 AHexGridManager::BorderSize;
float AHexGridManager::OddRowHorizontalOffset;
float AHexGridManager::TileHorizontalOffset;
float AHexGridManager::TileVerticalOffset;

TSubclassOf<AHexTile> AHexGridManager::AttackerHexTile;
TSubclassOf<AHexTile> AHexGridManager::DefenderHexTile;
TSubclassOf<AHexTile> AHexGridManager::DefaultHexTile;
TSubclassOf<AHexTile> AHexGridManager::SentinelHexTile;

TArray<AHexTile *> AHexGridManager::DefenderTiles;
TArray<AHexTile *> AHexGridManager::AttackerTiles;
TArray<TArray<AUnit *>> AHexGridManager::UnitGrid;

TArray<AUnit*> AHexGridManager::DefenderUnits;
TArray<AUnit*> AHexGridManager::AttackerUnits;

EHexTileType AHexGridManager::GetTileType(const FIntPoint &Cord)
{
	return HexGrid[Cord.X][Cord.Y]->TileType;
}

AUnit *AHexGridManager::GetUnit(const FIntPoint &Cord)
{
	return UnitGrid[Cord.X][Cord.Y];
}

void AHexGridManager::ChangeUnitPosition(AUnit *Unit, const FIntPoint &Cord)
{
	UnitGrid[Unit->CurrentCord.X][Unit->CurrentCord.Y] = nullptr; // clean your previous location
	UnitGrid[Cord.X][Cord.Y] = Unit;							  // UnitGrid Update

	Unit->CurrentCord = Cord; // update Unit Index

	Unit->SetActorLocation(HexGrid[Cord.X][Cord.Y]->GetActorLocation()); // Move visuals of the unit
}

void AHexGridManager::RemoveUnit(AUnit *Unit)
{
	FIntPoint Cord = Unit->CurrentCord;
	UnitGrid[Cord.X][Cord.Y] = nullptr; // Remove unit from gameplay grid

	// Unit->SetActorLocation(HexGrid[0][0]->GetActorLocation());
	Unit->Destroy();
}

#pragma region Coordinates tools

TArray<AUnit *> AHexGridManager::AdjacentUnits(const FIntPoint &BaseCord)
{ // Returns 6 elements Array, elements can be nullptr
	TArray<AUnit *> Units;
	for (int side = 0; side < 6; side++)
	{
		FIntPoint Cord = AdjacentCord(BaseCord, side);
		AUnit *Neighbour = UnitGrid[Cord.X][Cord.Y];
		// if (Neighbour != nullptr)
		Units.Add(Neighbour);
	}
	return Units;
}

AUnit *AHexGridManager::GetShotTarget(FIntPoint StartCord, const int32 Side)
{
	while (HexGrid[StartCord.X][StartCord.Y]->TileType != EHexTileType::SENTINEL)
	{
		StartCord += Directions[Side];
		AUnit *Target = UnitGrid[StartCord.X][StartCord.Y];
		if (Target != nullptr)
			return Target;
	}
	return nullptr;
}

AUnit *AHexGridManager::GetDistantUnit(FIntPoint StartCord, const int32 Side, const int32 Distance)
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

FIntPoint AHexGridManager::GetDistantCord(FIntPoint &StartCord, const int32 Side, const int32 Distance)
{
	FIntPoint NewCord = StartCord;
	for (int32 i = 0; i < Distance; i++)
	{
		NewCord += Directions[Side];
	}
	return NewCord;
}

bool AHexGridManager::IsAdjacent(const FIntPoint &Cord1, const FIntPoint &Cord2)
{
	int32 Index = Directions.Find(Cord2 - Cord1);

	return (Index == INDEX_NONE) ? false : true;
}

int32 AHexGridManager::AdjacentSide(const FIntPoint &Cord1, const FIntPoint &Cord2)
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

FIntPoint AHexGridManager::AdjacentCord(const FIntPoint &BaseCord, int32 Side)
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

int32 AHexGridManager::AdjacentCordSide(int32 Side)
{
	/**
	 * Convert side of a cord to its corresponding adjacent cord side
	 * ex. 2 -> 5   //  (current cord side) -> (adjacent cord side)
	 * ___
	 *    \___
	 * __2/5  \
	 *    \___/
	 *
	 * @param Side side number of current cord
	 * @return side number of a cord, which shares a side with a current cord
	 */

	return (Side + 3) % 6;
}

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
	GridWidth += floor(GridHeight / 2); // adjustment for Axial grid system
}

// #include <typeinfo>

void AHexGridManager::InitHexGridArray()
{

	HexGrid.SetNumZeroed(GridWidth); // __ how it works exactly - print the content / debugger
	UnitGrid.SetNumZeroed(GridWidth);

	// auto x = typeid(HexGrid2DArray[0]).name();
	// FString::Printf(x);

	// if (UnitGrid2DArray[0] == std::nullptr_t)

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
			const bool oddRow = y % 2 == 0; // Sentinel Rows add aditional row

			const float XTilePos = x * TileHorizontalOffset + y * OddRowHorizontalOffset;
			const float YTilePos = y * TileVerticalOffset;
			UWorld* world = GEngine->GameViewport->GetWorld();
			AHexTile *newTile = world->SpawnActor<AHexTile>(GetTileToSpawn(x, y, oddRow),
																 FVector(FIntPoint(XTilePos, YTilePos)),
																 FRotator::ZeroRotator);
			newTile->TileIndex = FIntPoint(x, y);

			if (current_spawn == EHexTileType::SENTINEL)
			{
				newTile->SetActorLabel(FString::Printf(TEXT("Tile_Sentinel_%d-%d"), x, y));
			}
			else if (current_spawn == EHexTileType::DEFAULT)
			{
				newTile->SetActorLabel(FString::Printf(TEXT("Tile_Default_%d-%d"), x, y));
			}
			else if (current_spawn == EHexTileType::ATTACKER_SPAWN)
			{
				newTile->SetActorLabel(FString::Printf(TEXT("Tile_Attacker_Spawn_%d-%d"), x, y));
				AttackerTiles.Add(newTile);
			}
			else if (current_spawn == EHexTileType::DEFENDER_SPAWN)
			{
				newTile->SetActorLabel(FString::Printf(TEXT("Tile_Defender_Spawn_%d-%d"), x, y));
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

	return (gameplay_height_start <= y && y < gameplay_height_end)							 // Height
		   && ((gameplay_width_start <= x && x < gameplay_width_even_end && !bOddRow)		 // even row width
			   || (gameplay_width_start + 1 <= x && x < gameplay_width_odd_end && bOddRow)); // odd row width
}

TSubclassOf<AHexTile> AHexGridManager::GetTileToSpawn(const int32 x, const int32 y, bool bOddRow)
{
	TSubclassOf<AHexTile> TileToSpawn = SentinelHexTile; // Default value for hex tile is Sentinel Tile
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
		else if (x == GridWidth - BorderSize - 1 - floor(y / 2)) // last column
		{
			TileToSpawn = DefenderHexTile;
			current_spawn = EHexTileType::DEFENDER_SPAWN;
		}
	}

	return TileToSpawn;
}

void AHexGridManager::SpawnUnits()
{
	/*
	* Placing Units used in combat on their "Spawn Points" near the area of the gameplay board where they are visible to the players.
	*/
	
	// spawning attacker units
	for (int32 i = 0; i < AttackerUnits.Num(); i++)
	{
		AttackerUnits[i]->Controller = EPlayer::ATTACKER;

		FIntPoint SpawnCord = AttackerTiles[i]->TileIndex; // Get spawn location
		SpawnCord += Directions[3];  // Move to a spot outside of the map near spawn point

		ChangeUnitPosition(AttackerUnits[i], SpawnCord); // Adding Unit to the Gameplay Array
		
	}

	// spawning defender units
	for (int32 i = 0; i < DefenderUnits.Num(); i++)
	{
		DefenderUnits[i]->Controller = EPlayer::DEFENDER;

		FIntPoint SpawnCord = DefenderTiles[i]->TileIndex; // Get spawn location
		SpawnCord += Directions[0]; // Move to a spot outside of the map near spawn point

		ChangeUnitPosition(DefenderUnits[i], SpawnCord); // Adding Unit to the Gameplay Array
	}

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

void AHexGridManager::PostInitializeComponents()
{ // PrintString, maybe in constructor?
	Super::PostInitializeComponents();
	GridWidth = UGridWidth;
	GridHeight = UGridHeight;
	OddRowHorizontalOffset = UOddRowHorizontalOffset;
	TileHorizontalOffset = UTileHorizontalOffset;
	TileVerticalOffset = UTileVerticalOffset;

    AttackerHexTile = UAttackerHexTile;
	DefenderHexTile = UDefenderHexTile;
	DefaultHexTile = UDefaultHexTile;
	SentinelHexTile = USentinelHexTile;

	DefenderUnits = UDefenderUnits;
	AttackerUnits = UAttackerUnits;

	HexGrid.Empty();
	DefenderTiles.Empty();
	AttackerTiles.Empty();
	UnitGrid.Empty();
}

void AHexGridManager::BeginPlay()
{
	Super::BeginPlay();
	
	AGameplayManager::GameSetup();
	GenerateGrid();
	SpawnUnits();
	SimpleAutomaticTests();
}

// Sets default values
AHexGridManager::AHexGridManager()
{
	GridWidth = 5;
	GridHeight = 5;

	BorderSize = 1;

	AutomaticTest = EAutomaticTestsList::EMPTY;
}


void AHexGridManager::SimpleAutomaticTests()
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
				AGameplayManager::InputListener(AttackerUnits[i]->CurrentCord);
				AGameplayManager::InputListener(AttackerUnits[i]->CurrentCord + Directions[0]);
			}
			if (i < DefenderUnits.Num())
			{
				AGameplayManager::InputListener(DefenderUnits[i]->CurrentCord);
				AGameplayManager::InputListener(DefenderUnits[i]->CurrentCord + Directions[3]);
			}
		}
		return;
	}
}

#pragma endregion
