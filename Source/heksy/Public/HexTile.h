/*****************************************************************//**
 * \file   HexTile.h
 * \brief  Basic board element, holds several metric about its own position.
 * 

 *********************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GameplayEnums.h"

#include "HexTile.generated.h"

class UStaticMeshComponent;


UCLASS()  
class HEKSY_API AHexTile : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Tile")
	FIntPoint TileIndex;  // Tile Cords


	EHexTileType TileType;   // logical tile type
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tile")
	UStaticMeshComponent *TileMesh;  // U: visible mesh

public:
	AHexTile(); // INIT
};
