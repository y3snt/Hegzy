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

	

	//SymbolTest = FSubObject<FrontSymbol>(TEXT("SymbolMesh"));  // TODO: shared_ptr/unique; this is mesh for the tile
	//SymbolTest->SetupAttachment(RootComponent);  // attach component to the root / container

	CurrentRotation = 0;
}

FIntPoint AUnit::Neighbour(int32 Side)
{
	return CurrentCord + Directions[Side];
}


/*
ASymbol* AUnit::GetSymbol(int32 side)
{
	//TArray<ASymbol*> Symbols = { FrontSymbol, };

	return nullptr;
}
*/



// Called to bind functionality to input
void AUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);  //TODO fix it
}
/*

void AUnit::Move(const FIntPoint& EndCord)
{ 
	int32 NewDirection = DirectionToSide(EndCord - CurrentCord);  // get direction  ? why neighbour.find

	//Rotate(NewDirection)
	//TODO: if shields: // maybe check for every unit
	
	//HegzyEvents::OnUnitMoved(CurrentCord); // -> GameMG spr czy nie giniemy
	HegzyEvents::OnUnitMoved(1); // -> GameMG spr czy nie giniemy
/*
	Action(CurrentCord)


	TransformPosition(EndCord) // change CurrentCord
	HegzyEvents.OnUnitMoved(CurrentCord);
	Action(CurrentCord)

}
*/
/*
Unit::Rotate(x)
	Cord Directions[6]  // 6 different hex locations in regards of our won
	int Rotation = x // 0-5 number
	model.rotation = 30 * x // + naszeustawienie_hexow;
	0 - przod
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