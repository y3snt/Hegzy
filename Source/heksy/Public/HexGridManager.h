// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "HexTile.h"

#include "HexGridManager.generated.h"



UCLASS()
class HEKSY_API AHexGridManager : public AActor
{
	GENERATED_BODY()



protected:
	TArray<TArray<AHexTile*>> HexGrid2DArray;  // pointers to hex objects / tiles

	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")   // __ ? we can change the value of a blueprint later
	int32 GridWidth;   // no tiles horizonally

	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	int32 GridHeight;  // no tiles horizonally vertically


	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	float OddRowHorizontalOffset;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	float TileHorizontalOffset;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Layout")
	float TileVerticalOffset;

	UPROPERTY(EditAnywhere, Category = "HexGrid|Setup")
	TSubclassOf<AHexTile> GrassHexTile;


public:	
	// Sets default values for this actor's properties
	AHexGridManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;   // __ why virtual and override??

};
