/*****************************************************************//**
 * \file   HexGridManager.h
 * \brief  Main file - Responsible for board generation and management
 * 
 *********************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"


#include "HexTile.h"
#include "Unit.h"

#include "GameplayEnums.h"


#include "HexGridManager.generated.h"


UENUM()
enum class EAutomaticTestsList : uint8
{
	INVALID,
	EMPTY,
	BASIC_UNIT_SETUP,
	MAX UMETA(Hidden)
};



UCLASS()
class HEKSY_API AHexGridManager : public AActor
{
	GENERATED_BODY()

private:
	static EHexTileType current_spawn;
	const static TArray<FIntPoint> Directions;
	static TArray<TArray<AHexTile*>> HexGrid;  // pointers to hex objects / tiles

#pragma region Gameplay Board Properties
	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	int32 UGridWidth;   // number of tiles horizonally
	static int32 GridWidth;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	int32 UGridHeight;  // number of tiles horizonally vertically
	static int32 GridHeight;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	int32 UBorderSize;
	static int32 BorderSize;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	float UOddRowHorizontalOffset;
	static float OddRowHorizontalOffset;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	float UTileHorizontalOffset; 
	static float TileHorizontalOffset;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	float UTileVerticalOffset;
	static float TileVerticalOffset;
#pragma endregion

#pragma region Hex Tile Actors
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
#pragma endregion
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; // INIT
	virtual void PostInitializeComponents() override;   // Unreal INIT
	
	static void BlueprintsCheck();  // stops the program if the properties aren't setup
	static void InitHexGridArray(); // Fixes the issues related to Unreal handling of static properties
	static void SpawnTiles();		// Main board generation function
	static void AdjustGridSize();	// Modifies the starting properties to be used in the map generation

	static bool isGameplayTile(const int32 x, const int32 y, bool bOddRow);  // given coordinates returns true if tile is inside the gameplay area
	static TSubclassOf<AHexTile> GetTileToSpawn(const int32 x, const int32 y, bool bOddRow); // Tool of SpawnTiles() which returns proper HexTileActor

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

	/**
	 * Places Units from the scene on the edge of the gameplay board.
	 */
	static void SpawnUnits();
	/**
	 * Based on AutomaticTest Enum value launches a set of pre recorded instructions for testing purposes.
	 */
	void SimpleAutomaticTests();

	AHexGridManager(); // INIT
	
	/**
	 * Given tile cords returns tile type.
	 * Mostly used to verify if the tile is in gameplay area, or if the tile is the proper summon location for a unit
	 * @param Cord
	 * @return EHexTileType
	 */
	static EHexTileType GetTileType(const FIntPoint& Cord);
	
	/**
	 * Given tile cors return pointer to a Unit.
	 * 
	 * @param Cord
	 * @return AUnit*
	 */
	static AUnit* GetUnit(const FIntPoint& Cord);
	
	/**
	 * Modifies the visual state of the unit and its placement in the gameplay logic arrays.
	 * Function assumes the move is legal.
	 * @param Unit
	 * @param Cord
	 */
	static void ChangeUnitPosition(AUnit* Unit, const FIntPoint& Cord);

	/**
	 * Return true if the two tiles are neighbours.
	 * 
	 * @param Cord1
	 * @param Cord2
	 * @return bool
	 */
	static bool IsAdjacent(const FIntPoint& Cord1, const FIntPoint& Cord2);

	/**
	 * Assuming tiles are adjacent it returns the direction from the first tile to the second.
	 * 
	 * @param Cord1
	 * @param Cord2
	 * @return Direction INT
	 */
	static int32 AdjacentSide(const FIntPoint& Cord1, const FIntPoint& Cord2);
	
	/**
	 *  Returns the Coordinates of a tile adjacent to BaseCord in the direction "Side".
	 * 
	 * @param BaseCord
	 * @param Side
	 * @return FIntPoint Cord
	 */
	static FIntPoint AdjacentCord(const FIntPoint& BaseCord, int32 Side);

	/**
	 * return (Side + 3) % 6.
	 * 
	 * @param Side
	 * @return 
	 */
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
	 * Returns Cord of a tile located Distance tiles away from the StartCord in the Side direction.
	 * 
	 * @param StartCord
	 * @param Side
	 * @param Distance
	 * @return 
	 */
	static FIntPoint GetDistantCord(FIntPoint& StartCord, const int32 Side, const int32 Distance);

	/**
	 * Removes Unit from the Gameplay arrays and calls its destructor.
	 * 
	 * @param Unit
	 */
	static void RemoveUnit(AUnit* Unit);

	/**
	 * Main function that generates starting gameplay board.
	 * 
	 */
	static void GenerateGrid();
};
