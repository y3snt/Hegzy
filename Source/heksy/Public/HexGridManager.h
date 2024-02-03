// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"


#include "HexTile.h"
#include "Unit.h"

#include "GameplayEnums.h"
//#include "GameplayConstants.h"

#include "HexGridManager.generated.h"


UENUM()
enum class EAutomaticTestsList : uint8  // __ why uint?
{
	INVALID,
	EMPTY,
	BASIC_UNIT_SETUP,
	MAX UMETA(Hidden)  // __ ???
};



UCLASS()
class HEKSY_API AHexGridManager : public AActor
{
	GENERATED_BODY()

private:
	static EHexTileType current_spawn;  // ??
	const static TArray<FIntPoint> Directions;
	static TArray<TArray<AHexTile*>> HexGrid;  // pointers to hex objects / tiles

	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")   // __ ? we can change the value of a blueprint later
	int32 UGridWidth;   // no tiles horizonally
	static int32 GridWidth;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	int32 UGridHeight;  // no tiles horizonally vertically
	static int32 GridHeight;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	int32 UBorderSize;
	static int32 BorderSize;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	float UOddRowHorizontalOffset; // TODO: should this be Uproperty
	static float OddRowHorizontalOffset;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	float UTileHorizontalOffset; 
	static float TileHorizontalOffset;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	float UTileVerticalOffset;
	static float TileVerticalOffset;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Setup")
	TSubclassOf<AHexTile> UAttackerHexTile;
	static TSubclassOf<AHexTile> AttackerHexTile;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Setup")
	TSubclassOf<AHexTile> UDefenderHexTile;
	static TSubclassOf<AHexTile> DefenderHexTile;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Setup")
	TSubclassOf<AHexTile> UDefaultHexTile;
	static TSubclassOf<AHexTile> DefaultHexTile;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Setup")
	TSubclassOf<AHexTile> USentinelHexTile;
	static TSubclassOf<AHexTile> SentinelHexTile;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;   
	
	static void BlueprintsCheck();  // stops the program if the properties aren't setup
	static void InitHexGridArray();
	static void SpawnTiles();
	static void AdjustGridSize();

	static bool isGameplayTile(const int32 x, const int32 y, bool bOddRow);
	static TSubclassOf<AHexTile> GetTileToSpawn(const int32 x, const int32 y, bool bOddRow);

public:
	UPROPERTY(EditAnywhere, Category = "AutomaticTests|Basic")
	EAutomaticTestsList AutomaticTest;


	static TArray<AHexTile*> DefenderTiles;  // TODO: move to protected
	static TArray<AHexTile*> AttackerTiles;  // TODO: move to protected
	static TArray<TArray<AUnit*>> UnitGrid;  // pointers to units on hex grid

	UPROPERTY(EditAnywhere, Category = "GameplayProperties|Map")
	TArray<AUnit*> UDefenderUnits;
	static TArray<AUnit*> DefenderUnits;
	
	UPROPERTY(EditAnywhere, Category = "GameplayProperties|Map")
	TArray<AUnit*> UAttackerUnits;
	static TArray<AUnit*> AttackerUnits;

	static void SpawnUnits();
	void SimpleAutomaticTests();

	AHexGridManager();

	static EHexTileType GetTileType(const FIntPoint& Cord);
	static AUnit* GetUnit(const FIntPoint& Cord);
	
	static void ChangeUnitPosition(AUnit* Unit, const FIntPoint& Cord);

	static bool IsAdjacent(const FIntPoint& Cord1, const FIntPoint& Cord2);
	static int32 AdjacentSide(const FIntPoint& Cord1, const FIntPoint& Cord2); // Rename to shared side
	static FIntPoint AdjacentCord(const FIntPoint& BaseCord, int32 Side); //? TODO add static
	static int32 AdjacentCordSide(int32 Side);


	/**
	 * Get a reference to the first Unit hit by a bow.
	 * 
	 * @param StartCord
	 * @param Side
	 * @return 
	 */
	static AUnit* GetShotTarget(FIntPoint StartCord, const int32 Side);

	/**
	 * Get a Unit from a hex tile placed "Distance" tiles away.
	 * 
	 * @param StartCord
	 * @param Side
	 * @param Distance
	 * @return 
	 */
	static AUnit* GetDistantUnit(FIntPoint StartCord, const int32 Side, const int32 Distance);

	/**
	 * Get a Tile placed "Distance" tiles away from StartCord.
	 *
	 * @param StartCord
	 * @param Side
	 * @param Distance
	 * @return
	 */
	static EHexTileType GetDistantTileType(FIntPoint StartCord, const int32 Side, const int32 Distance);

	/**
	 * Lists Units around a specific Hex Tile.
	 * 
	 * @param BaseCord
	 * @return Returns 6 elements Array, elements can be nullptr
	 */
	static TArray<AUnit*> AdjacentUnits(const FIntPoint& BaseCord);

	/**
	 * .
	 * 
	 * @param StartCord
	 * @param Side
	 * @param Distance
	 * @return 
	 */
	static FIntPoint GetDistantCord(FIntPoint& StartCord, const int32 Side, const int32 Distance);

	static void RemoveUnit(AUnit* Unit);

	static void GenerateGrid();
};
