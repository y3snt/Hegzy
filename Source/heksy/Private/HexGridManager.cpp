// Fill out your copyright notice in the Description page of Project Settings.

#include <iostream>
#include "HexGridManager.h"

// Sets default values
AHexGridManager::AHexGridManager()
{
 	

}

// Called when the game starts or when spawned
void AHexGridManager::BeginPlay()
{
	Super::BeginPlay();
	
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
			if (x == GridWidth && oddRow)
			{
				continue;
			}
			const float xPos = oddRow ? (x * TileHorizontalOffset) + OddRowHorizontalOffset : x * TileHorizontalOffset;
			const float yPos = y * TileVerticalOffset;

			TSubclassOf<AHexTile> tileToSpawn = GrassHexTile;
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



