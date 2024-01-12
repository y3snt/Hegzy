// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit.h"


// Sets default values
AUnit::AUnit()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));  // "container" for other components
	UnitMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UnitMesh"));  // TODO: shared_ptr/unique; this is mesh for the tile
	UnitMesh->SetupAttachment(RootComponent);  // attach component to the root / container

	

	//SymbolTest = FSubObject<FrontSymbol>(TEXT("SymbolMesh"));  // TODO: shared_ptr/unique; this is mesh for the tile
	//SymbolTest->SetupAttachment(RootComponent);  // attach component to the root / container

	CurrentRotation = 0;
}




FIntPoint AUnit::Neighbour(int32 Direction)
{
	return CurrentCord + directions[Direction];
}


/*
ASymbol* AUnit::GetSymbol(int32 side)
{
	//TArray<ASymbol*> Symbols = { FrontSymbol, };

	return nullptr;
}
*/

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();
}



// Called to bind functionality to input
void AUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

