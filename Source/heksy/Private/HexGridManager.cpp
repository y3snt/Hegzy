// Fill out your copyright notice in the Description page of Project Settings.

#include <iostream>
#include "HexGridManager.h"

// Sets default values
AHexGridManager::AHexGridManager() {}

// Called when the game starts or when spawned
void AHexGridManager::BeginPlay()
{
	Super::BeginPlay();
	BlueprintsCheck();

	// "+2" is to reserve space for sentinel tiles on each side of the board
	AdjustGridSize();

	/*if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f,
			FColor::Yellow, FString::Printf(TEXT("GridWidth equals %i"),
				GridWidth), true);
	*/

	InitHexGridArray();
	SpawnTiles();
	
}

void AHexGridManager::BlueprintsCheck()
{
	checkf(GrassHexTile != NULL, TEXT("no GrassHexTile"));
	checkf(DirtHexTile != NULL, TEXT("no DirtHexTile"));
	checkf(RockHexTile != NULL, TEXT("no RockHexTile"));
	checkf(SentinelHexTile != NULL, TEXT("no SentinelHexTile"));	
}

void AHexGridManager::AdjustGridSize() 
{
	GridWidth += 2;  // TODO: BorderSize * 2
	GridHeight += 2;
}

void AHexGridManager::InitHexGridArray() 
{
	HexGrid2DArray.SetNumZeroed(GridWidth);  // __ how it works exactly - print the content / debugger
	for (int32 i = 0; i < HexGrid2DArray.Num(); i++)
	{
		HexGrid2DArray[i].SetNumZeroed(GridHeight);  
		//std::cout << "siema";
	}
}

void AHexGridManager::SpawnTiles() {
	for (int32 y = 0; y < GridHeight; y++)
	{
		for (int32 x = 0; x < GridWidth; x++)
		{
			const bool oddRow = IsRowOdd(y);
			if (x == GridWidth - 1 && oddRow)  // makes the map symetric
				continue;
			
			AHexTile* newTile = GetWorld()->SpawnActor<AHexTile>(GetTileToSpawn(x, y, oddRow),
																	FVector(FIntPoint(GetXTilePos(oddRow, x), GetYTilePos(y))), 
																	FRotator::ZeroRotator);
			newTile->TileIndex = FIntPoint(x, y);
		}

	}
}

bool AHexGridManager::IsRowOdd(const int32 y) 
{
	return y % 2 == 0;  // Sentinel Rows add aditional row
}

bool AHexGridManager::IsTileSentinel(const int32 x, const int32 y, bool bOddRow)
{
	return y == 0						   // first row
		   || y == GridHeight - 1		   // last row
		   || x == 0					   // first column
		   || x == GridWidth - 2 && bOddRow // last odd column
		   || x == GridWidth - 1;		   // last even column
}

float AHexGridManager::GetXTilePos(const bool bIsRowOdd, const int32 x)
{
	return bIsRowOdd ? (x * TileHorizontalOffset) + OddRowHorizontalOffset : x * TileHorizontalOffset;
}

float AHexGridManager::GetYTilePos(const int32 y) 
{
	return y * TileVerticalOffset;
}

TSubclassOf<AHexTile> AHexGridManager::GetTileToSpawn(const int32 x, const int32 y, bool bOddRow)
{
	TSubclassOf<AHexTile> TileToSpawn = DirtHexTile;  // Default Tile

	if (IsTileSentinel(x, y, bOddRow)) {
		TileToSpawn = SentinelHexTile;
	}
	else if (x == 1) // first column
	{
		TileToSpawn = GrassHexTile;
	}
	else if (x == GridWidth - 3 && bOddRow || x == GridWidth - 2) // last column
	{
		TileToSpawn = RockHexTile;
	}

	return TileToSpawn;
}