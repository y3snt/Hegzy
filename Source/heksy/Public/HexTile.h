// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GameplayEnums.h"

#include "HexTile.generated.h"

class UStaticMeshComponent;

/*
UENUM()
enum class EHexTileType : uint8  // __ why uint?
{
	INVALID,
	GRASS,   // TODO: change to proper naming like: DEFAULT, SPAWN_1
	WATER,
	MAX UMETA(Hidden)  // __ ???
};
*/
UCLASS()  // __ ???
class HEKSY_API AHexTile : public AActor   // __ why HEKSY_API 
{
	GENERATED_BODY()   // __ ???

public:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Tile")
	FIntPoint TileIndex;


	EHexTileType TileType;   // logical tile type
protected:
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tile")  // U: property, that will be visible in the editor
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tile")
	UStaticMeshComponent *TileMesh;  // U: visible mesh

public:
	// Sets default values for this actor's properties
	AHexTile();
};
