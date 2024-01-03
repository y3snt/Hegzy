// Fill out your copyright notice in the Description page of Project Settings.

#include <iostream>
#include "HexGridManager.h"

// Sets default values
AHexGridManager::AHexGridManager()
{
 	

}


void AHexGridManager::blueprintsCheck()
{
	checkf(GrassHexTile != NULL, TEXT("no GrassHexTile"));
	checkf(DirtHexTile != NULL, TEXT("no DirtHexTile"));
	checkf(RockHexTile != NULL, TEXT("no RockHexTile"));
	checkf(SentinelHexTile != NULL, TEXT("no SentinelHexTile"));	
}


// Called when the game starts or when spawned
void AHexGridManager::BeginPlay()
{
	Super::BeginPlay();

	// "+2" is to reserve space for sentinel tiles on each side of the board
	GridWidth += 2;
	GridHeight += 2;

	/*if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f,
			FColor::Yellow, FString::Printf(TEXT("GridWidth equals %i"),
				GridWidth), true);
	*/

	HexGrid2DArray.SetNumZeroed(GridWidth);  // __ how it works exactly - print the content / debugger
	for (int32 i = 0; i < HexGrid2DArray.Num(); i++)
	{
		HexGrid2DArray[i].SetNumZeroed(GridHeight);  
		//std::cout << "siema";
	}

	for (int32 y = 0; y < GridHeight; y++)
	{
		for (int32 x = 0; x < GridWidth; x++)
		{
			const bool oddRow = y % 2 == 0;  // Sentinel Rows add aditional row
			if (x == GridWidth - 1 && oddRow)  // makes the map symetric
			{
				continue;
			}
			
			TSubclassOf<AHexTile> tileToSpawn = DirtHexTile;  // Default Tile

			if (y == 0)  // bottom row
			{
				tileToSpawn = SentinelHexTile;
			}
			else if (y == GridHeight - 1)  // top row
			{
				tileToSpawn = SentinelHexTile;
			}
			else if (x == 0)  // first column
			{
				tileToSpawn = SentinelHexTile;
			}
			else if (x == GridWidth - 2 && oddRow)    // last odd column
			{
				tileToSpawn = SentinelHexTile;
			}
			else if (x == GridWidth - 1)  // last even column
			{
				tileToSpawn = SentinelHexTile;
			}


			else if (x == 1) // first column
			{
				tileToSpawn = GrassHexTile;
			}
			else if (x == GridWidth - 3 && oddRow) // last odd column
			{
				tileToSpawn = RockHexTile;
			}
			else if (x == GridWidth - 2) // last even column
			{
				tileToSpawn = RockHexTile;
			}
			
			
			const float xPos = oddRow ? (x * TileHorizontalOffset) + OddRowHorizontalOffset : x * TileHorizontalOffset;
			const float yPos = y * TileVerticalOffset;

			AHexTile* newTile = GetWorld()->SpawnActor<AHexTile>(tileToSpawn, FVector(FIntPoint(xPos, yPos)), FRotator::ZeroRotator);
			newTile->TileIndex = FIntPoint(x, y);
		}

	}

	/*
	* 	Super::BeginPlay();
	
	HexGrid2DArray.SetNumZeroed(GridWidth);  // __ how it works exactly - print the content / debugger
	for (int32 i = 0; i < HexGrid2DArray.Num(); i++)
	{
		HexGrid2DArray[i].SetNumZeroed(GridHeight);
		//std::cout << "siema";
	}

	for (int32 y = 0; y < GridHeight; y++)
	{
		for (int32 x = 0; x < GridWidth; x++)
		{
			const bool oddRow = y % 2 == 1;
			const float xPos = oddRow ? (x * TileHorizontalOffset) + OddRowHorizontalOffset : x * TileHorizontalOffset;
			const float yPos = y * TileVerticalOffset;

			TSubclassOf<AHexTile> tileToSpawn = GrassHexTile;
			AHexTile* newTile = GetWorld()->SpawnActor<AHexTile>(tileToSpawn, FVector(FIntPoint(xPos, yPos)), FRotator::ZeroRotator);
			newTile->TileIndex = FIntPoint(x, y);
		}

	}
	*/
}



