// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"


#include "HexTile.h"
#include "Unit.h"

#include "GameplayEnums.h"
//#include "GameplayConstants.h"

#include "HexGridManager.generated.h"




UCLASS()
class HEKSY_API AHexGridManager : public AActor
{
	GENERATED_BODY()

private:
	
	void BlueprintsCheck();  // stops the program if the properties aren't setup
	void InitHexGridArray();
	void SpawnTiles();

	void AdjustGridSize();
	bool isGameplayTile(const int32 x, const int32 y, bool bOddRow);
	TSubclassOf<AHexTile> GetTileToSpawn(const int32 x, const int32 y, bool bOddRow);

	EHexTileType current_spawn;  // ??
	const static TArray<FIntPoint> Directions;


protected:
	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")   // __ ? we can change the value of a blueprint later
	int32 GridWidth;   // no tiles horizonally

	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	int32 GridHeight;  // no tiles horizonally vertically

	int32 BorderSize;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	float OddRowHorizontalOffset;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	float TileHorizontalOffset;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	float TileVerticalOffset;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Setup")
	TSubclassOf<AHexTile> AttackerHexTile;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Setup")
	TSubclassOf<AHexTile> DefenderHexTile;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Setup")
	TSubclassOf<AHexTile> DefaultHexTile;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Setup")
	TSubclassOf<AHexTile> SentinelHexTile;

	
	TArray<TArray<AHexTile*>> HexGrid;  // pointers to hex objects / tiles

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;   // __ why virtual and override??

public:
	TArray<AHexTile*> DefenderTiles;
	TArray<AHexTile*> AttackerTiles;
	TArray<TArray<AUnit*>> UnitGrid;  // pointers to units on hex grid

	EHexTileType GetTileType(const FIntPoint& Cord) const;
	AUnit* GetUnit(const FIntPoint& Cord);
	
	void ChangeUnitPosition(AUnit* Unit, const FIntPoint& Cord);
	void RotateUnit(AUnit* Unit, int32 Side);

	bool IsAdjacent(const FIntPoint& Cord1, const FIntPoint& Cord2);
	int32 AdjacentSide(const FIntPoint& Cord1, const FIntPoint& Cord2); // Rename to shared side
	FIntPoint AdjacentCord(const FIntPoint& BaseCord, int32 Side); //? TODO add static


	/**
	 * Get a reference to the first Unit hit by a bow.
	 * 
	 * @param StartCord
	 * @param Side
	 * @return 
	 */
	AUnit* GetShotTarget(FIntPoint StartCord, const int32 Side);

	/**
	 * Get a Unit from a hex tile placed "Distance" tiles away.
	 * 
	 * @param StartCord
	 * @param Side
	 * @param Distance
	 * @return 
	 */
	AUnit* GetDistantUnit(FIntPoint StartCord, const int32 Side, const int32 Distance);

	/**
	 * Get a Tile placed "Distance" tiles away from StartCord.
	 *
	 * @param StartCord
	 * @param Side
	 * @param Distance
	 * @return
	 */
	EHexTileType GetDistantTileType(FIntPoint StartCord, const int32 Side, const int32 Distance);

	/**
	 * Lists Units around a specific Hex Tile.
	 * 
	 * @param BaseCord
	 * @return Returns 6 elements Array, elements can be nullptr
	 */
	TArray<AUnit*> AdjacentUnits(const FIntPoint& BaseCord);

	/**
	 * .
	 * 
	 * @param StartCord
	 * @param Side
	 * @param Distance
	 * @return 
	 */
	FIntPoint GetDistantCord(FIntPoint& StartCord, const int32 Side, const int32 Distance);



	void RemoveUnit(AUnit* Unit);

	void GenerateGrid();

	// Sets default values for this actor's properties
	AHexGridManager();

	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	int32 test_val;

	static int32 s_test_val;

};
