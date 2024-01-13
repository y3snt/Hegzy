// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit.h"


// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();
}



// Sets default values
AUnit::AUnit()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));  // "container" for other components
	UnitMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UnitMesh"));  // TODO: shared_ptr/unique; this is mesh for the tile
	UnitMesh->SetupAttachment(RootComponent);  // attach component to the root / container

	//HegzEvent<int> TestEvent; //dziala
	//TestEvent += fun;
	//TestEvent(1);

	//SymbolTest = FSubObject<FrontSymbol>(TEXT("SymbolMesh"));  // TODO: shared_ptr/unique; this is mesh for the tile
	//SymbolTest->SetupAttachment(RootComponent);  // attach component to the root / container

	CurrentRotation = 0;
}

/*
FIntPoint AUnit::Neighbour(int32 Side)
{
	return CurrentCord + Directions[Side];
}
*/


/*
ASymbol* AUnit::GetSymbol(int32 side)
{
	//TArray<ASymbol*> Symbols = { FrontSymbol, };

	return nullptr;
}
*/

void AUnit::Rotate(int32 Side)
{
	/**
	 * Rotate the unit towards Side
	 * 
	 * @param Side {0, 1, ..., 5}
	 * @note this is an absolute rotation (not based on current rotation of the unit)
	 */
	CurrentRotation = Side;
	
	// 360 / 6 = 60 -> degrees needed to rotate unit
	// "Direction + 4" Accounts for global rotation setting for objects in the level
	this->SetActorRotation(FRotator(0, 60 * (Side + 4), 0), ETeleportType::TeleportPhysics); // TODO: 4 is "magic number" -- ?grid rotation
}


// Called to bind functionality to input
void AUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);  //TODO fix it
}

/**
 * Move this unit to EndCord
 * 
 * @param EndCord Position at which unit will be placed
 */
void AUnit::Move(const FIntPoint& EndCord)
{ 
	int32 NewDirection = DirectionToSide(EndCord - CurrentCord);  // get direction  ? why neighbour.find

	Rotate(NewDirection);
	//TODO: if shields: // maybe check for every unit
	
	//HegzyEvents::OnUnitMoved(CurrentCord); // -> GameMG spr czy nie giniemy
	//HegzyEvents::OnUnitMoved(1); // -> GameMG spr czy nie giniemy

	//Action(CurrentCord)


	//TransformPosition(EndCord) // change CurrentCord
	//HegzyEvents.OnUnitMoved(CurrentCord);
	//Action(CurrentCord)

}

/*

1 - prawy_przod
2 - prawy tyl
3 - tyl
4 - lewy tyl
5 - lewy przod

Unit::Action():
	for i, symbol in enumarate(Symbols[6]):
		if symbol is activatable:
			Cord AdjCord = current_cord + direction[i - rotation];
			symbol.action(AdjCord)
*/