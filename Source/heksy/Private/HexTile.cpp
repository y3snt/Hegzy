// Fill out your copyright notice in the Description page of Project Settings.


#include "HexTile.h"
#include <Components/SceneComponent.h>
#include <Components/StaticMeshComponent.h>

// Sets default values
AHexTile::AHexTile()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));  // "container" for other components
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh"));  // TODO: shared_ptr/unique; this is mesh for the tile
	TileMesh->SetupAttachment(RootComponent);  // attach component to the root / container
}
