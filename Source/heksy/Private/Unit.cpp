// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit.h"
#include "GameplayManager.h"
#include "Symbol.h"

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


ESymbols AUnit::GetFrontSymbol()
{ 
	/**
	 * Get Symbol on a front of the Unit
	 * 
	 * @return ESymbols
	 */
	return Symbols[0];
}

ESymbols AUnit::GetSymbol(int32 side)
{ 
	/**
	 * Get the Symbol on a given side of Unit
	 * 
	 * @param side must be absolute side of a hex tile (0-5)
	 * @return ESymbols 
	 * 
	 * @note converts absolute hex side to loacal unit side (applying unit rotation)
	 */
	return Symbols[(side - CurrentRotation + 6) % 6];
}

bool AUnit::CanAttack()
{
	/**
	 * Return true if Unit can perform an attack from the front side
	 * 
	 * @return true if can attack
	 * @note returns true if action performed by the Unit can kill or move an enemy
	 */
	
	// Active == can affect unit
	TArray<ESymbols> AttackSymbols = {
		ESymbols::SWORD,
		ESymbols::SPEAR,
		ESymbols::PUSH,
		ESymbols::BOW
	};

	return AttackSymbols.Find(GetFrontSymbol()) != INDEX_NONE;
}


bool AUnit::CanDefend(int32 Side, ESymbols AttackerSymbol)
{
	/**
	 * Return true if Unit can block action from given Side
	 * 
	 * @param Side of a Unit, from which it could perform a block
	 * @return true if can block
	 */
	
	ESymbols Symbol = GetSymbol(Side);
	if (Symbol == ESymbols::SHIELD && AttackerSymbol != ESymbols::PUSH)  // Does Unit have a shield?
		return true;
	
	return false;
}

void AUnit::Damage(int32 AttackSide, ESymbols AttackerSymbol) 
{
	/**
	 * Take damage from AttackSide, if cannot defend - dies
	 * 
	 * @param AttackSide
	 */
	if(!CanDefend(AttackSide + 3, AttackerSymbol)) {
		AGameplayManager::KillUnit(this);
	}

}

void AUnit::Action()
{
	for (int32 side = 0; side < 6; side++)
	{
		ESymbols Symbol = GetSymbol(side);

		//if(Cast<IAction>(Symbol))
		//	Symbol.Action(this, side);

	}
}

void AUnit::PassiveAction(int32 Side)
{
	ESymbols Symbol = GetSymbol(Side);

	//if(Cast<IPassiveAction>(Symbol))
	//	Symbol.PassiveAction(this, Side);
}

/**
 * Move this unit to EndCord
 * 
 * @param EndCord Position at which unit will be placed
 */
 /*
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
*/

/*

1 - prawy_przod
2 - prawy tyl
3 - tyl
4 - lewy tyl
5 - lewy przod

*/

/*
AUnit::Action():
	for i, symbol in enumarate(Symbols[6]):
		if symbol is activatable:
			Cord AdjCord = current_cord + direction[i - rotation];
			symbol.action(AdjCord)
*/