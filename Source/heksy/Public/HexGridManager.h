// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "HexTile.h"
#include "Unit.h"


#include "HexGridManager.generated.h"


UENUM()
enum class EHexTileType : uint8  // __ why uint?
{
	INVALID,
	SENTINEL,   
	ATTACKER,
	DEFENDER,
	DEFAULT,
	MAX UMETA(Hidden)  // __ ???
};

UCLASS()
class HEKSY_API AHexGridManager : public AActor
{
	GENERATED_BODY()

	void BlueprintsCheck();  // stops the program if the properties aren't setup
	void InitHexGridArray();
	void SpawnTiles();

	void AdjustGridSize();
	bool IsRowOdd(const int32 y);
	bool isGameplayTile(const int32 x, const int32 y, bool bOddRow);
	float GetXTilePos(const int32 x, const int32 y);
	float GetYTilePos(const int32 y);
	TSubclassOf<AHexTile> GetTileToSpawn(const int32 x, const int32 y, bool bOddRow);

public:
	void GenerateGrid();
	TArray<AHexTile*> DefenderTiles;
	TArray<AHexTile*> AttackerTiles;
	TArray<TArray<AUnit*>> UnitGrid2DArray;  // pointers to units on hex grid
	TArray<TArray<AHexTile*>> HexGrid2DArray;  // pointers to hex objects / tiles


private:
	EHexTileType current_spawn;


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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;   // __ why virtual and override??

public:	
	// Sets default values for this actor's properties
	AHexGridManager();
};
