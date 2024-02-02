// Fill out your copyright notice in the Description page of Project Settings.


#include "Symbol.h"
#include "HexGridManager.h"


// Sets default values
ASymbol::ASymbol()
{

}

// Called when the game starts or when spawned
void ASymbol::BeginPlay()
{
	//Super::BeginPlay();
	
}

ESymbols ASymbol::ToEnum() {
	return SymbolEnum;
}

// Sword.cpp
/*
void ASword::Action(AUnit* Unit, int32 Side) // Adjacent Attack
{

	AUnit* Target = AHexGridManager::GetUnit(AHexGridManager::AdjacentCord(Unit->CurrentCord, Side));
	if (Target && Target->Controller != Unit->Controller)
		Target->Damage(Side);
}
*/

#pragma region ComponentTheory
/*
IActionable, IPasive, 

class Sword : IActionable
	Action()


#include damage
#include 
class Abc : IActive, IReactive
	Action()
		damage.effect1
		effect2
		
	Reaction()
		effect3
		effect4


#include damage

Plik Symbole:




Symbol mieczotarcza = new Symbol([damage.effect1, effect2, ..])
print(mieczotarcza.tags)


Unit:
	Symbole:
		Efekty:
			SubEfekty:
	



*/

// ==== Symbole DEMO =====
/*	
W?�cznia
	Action()
	PassiveAction()

Sword
	Action()
		logic - ex with Effects

sword.Action(Cord);
	
Shield
	Reaction()

?uk
	Action()
	
Odepchni?cie
	Action()



Action() - will be used in Unit

Unit::Action()  /// OLD FUNCTION
	foreach (i, symbol) : symbols
		if symbol isInstance(IActionable)
			cord ActionCord = CurrentCord + direction(i)  // or iCord, where i will be converted to direction, so dir[i]
			symbol.Action(CurrentCord)   // current cord - the cord on  | or adjCord - on which the action will be executed - probably better


PassiveAction() - will be used in GameManager


TileArray
Grid
*/


// ==== Sub Efekty ====
/* 

Melee - dzia?a na polu obok
//Rzut(dystans) - dzia?a na polu obok nas oddalonym o DYSTANS
Zasi?gowy(zasi?g) - dzia?a na pierwszego napotkanego przeciwnika w zakresie ZASI?G
//Pocisk(zasi?g) - dzia?a na pierwsz? napotkan? jednotk? w zakresie ZASI?G

//Friendly_Fire_Damage - deal damage to a tile
Normal_Damage - deal damage to a tile only if it's an enemy

Damage_block - if damage applied came from that direction, ignore it

Push(power) - moves a unit, if the tile it moves to is occupied or illegal. unit dies



*/




#pragma endregion 


#pragma region Gameplay Management

// 	=== ENTRY POINT ===
/* 

GameInput::Tick()
	if LeftMouseClick -> Tile:  // + map tile to tileCord
		// Cord SelectedTile = MapMousePosToCord()
		GameManager::Listener(Tile)
		GameVisuals::Highlight(Tile)


*/

//== = GAMEMANAGER ==== =
/*
PlayerTurn = Enum.Player1;
//Cord LastInput = null;  // ?? is it needed

// Unit *CurrentSelectedUnit = nullptr; //unitjakis  TODO: check if shared_ptr is needed
Unit &CurrentSelectedUnit = null;  // this must be pointer if we want null

GameManager::SwitchPlayerTurn()
	PlayerTurn = (PlayerTurn == Enum.Player1) ? Enum.Player2 : Enum.Player1;

GameManager::Listener(Cord)

	if IsFriendlyUnitOn(Cord):  // wybor jednostki
		//LastInput = Cord
		CurrrentSelectedUnit = &UnitsArray[Cord];  // ? pass by reference

	elif CurrrentSelectedUnit != null && IsLegalMove(Cord):   // or just CurrentSelectedUnit
		CurrrentSelectedUnit->Move(Cord)

		CurrrentSelectedUnit = null
		GameManager::SwitchPlayerTurn()
		

GameManager::IsLegalMove(Cord)   // if pushed: check if not legal move => destroy
	if HexGridManager.IsTileSentinel(Cord)//TODO obsluga tarcz
		return false;
	
	return true;

GameManager::CheckPositions(Cord)
	for neighbour(q, r) : neighbours(Cord)
		if Units[q][r] != null:  // How nulls work in unreal arrays??


bool GameManager::IsUnitOnCord(Cord)
	return Units[q][r] != null

bool GameManager::IsEnemyUnitOnCord(Cord)
	retrun IsUnitOnCord(Cord) && Units[q][r].Owner != PlayerTurn;


bool GameManager::IsFriendlyUnitOnCord(Cord)
	retrun IsUnitOnCord(Cord) && Units[q][r].Owner == PlayerTurn;



*/

// arr[q][r] zawiera Cord(q, r)

//==== UNIT ====
/* 

Unit {
	Cord CurrentCord = null;
}

Unit::Move(EndCord)
	int new_direction = Neighbor.find(EndCord - CurrentCord)  // get direction  ? why neighbour.find
	Rotate(new_direction)
	if shields: // maybe check for every unit
		SendMoveEvent(CurrentCord) -> GameMG spr czy nie giniemy

	Action(CurrentCord)


	TransformPosition(EndCord) // change CurrentCord
	SendMoveEvent(CurrentCord)
	Action(CurrentCord)




Unit::Rotate(x)
	Cord Directions[6]  // 6 different hex locations in regards of our won
	int Rotation = x // 0-5 number
	model.rotation = 45 * x // + naszeustawienie_hexow;
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

#pragma endregion





#pragma region Small Scripts
// == = AXIAL CORDINATE SYSTEM == =
/*

unit get_stuff(x, y)
	x += najmniejsza_wartosc_w_arreyu
	return array[x, y]





*/

#pragma endregion






#pragma region Stuff I would like to have


/*
is there a shield?
is there an enemy spear on this tile and from which direction it comes




*/



/*
Cool scripts:

we have a tile
now we check that there are actually neighbours so we want to get only their symbols that align with us


So someone in Front of us (our 0) is also rotated toward us (if our rotation is 0, then his is 3)

Code:
our_rotation .. their_rotation  .. contact_rotation





*/


#pragma endregion




/*
Yi = 0  // side
R1 = 0  // U.rotation

U2 = 0

U1 -> OnMoveEvent(this, currentCord)

GameplayManager::
	?OnMove(U1, cord) -> CheckPositions(U1, cord)


3 4 5 0 1 2  <- Xi
0 1 2 3 4 5  <- Yi


GameplayManager::CheckPositions(Unit, cord) 
	for Y, ajdCord in enumerate(ajd_Cords)
		X = (Y + 3) % 6 // super 3
		Y -= Unit.Rotation
		U2 = Units[adjCord] // != null
		U2.Symbols(X - U2.Rotation)










*/