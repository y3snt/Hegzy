#include "GameplayManager.h"
#include "Symbol.h"

#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::White, String)

#pragma region StaticMembers

int32 AGameplayManager::UnitsLeftToBeSummoned;
EPlayer AGameplayManager::CurrentPlayer;

AUnit* AGameplayManager::SelectedUnit = nullptr;
int32 AGameplayManager::AttackerUnitsAlive = 0;
int32 AGameplayManager::DefenderUnitsAlive = 0;

#pragma endregion


#pragma region Tools

void AGameplayManager::SwitchPlayerTurn()
{ // Currently works only for 2 players
	CurrentPlayer = (CurrentPlayer == EPlayer::ATTACKER) ? EPlayer::DEFENDER : EPlayer::ATTACKER;
}

bool AGameplayManager::IsLegalMove(FIntPoint Cord, int32& ResultSide)
{
	// Check if Cord is adjacent to SelectedUnit
	ResultSide = AHexGridManager::AdjacentSide(SelectedUnit->CurrentCord, Cord);  
	if (ResultSide == INDEX_NONE)
		return false;

	// Check if there no Unit in this spot
	AUnit* EnemyUnit = AHexGridManager::GetUnit(Cord);
	if (EnemyUnit == nullptr)
		return true;

	// Check if SelectedUnit can attack from the front, cause SelectedUnit will rotate before attacking
	int32 EnemySide = AHexGridManager::AdjacentCordSide(ResultSide);
	ASymbol* AttackSymbolPointer = SelectedUnit->GetFrontSymbol();

	if(AttackSymbolPointer == nullptr) 
		return false;

	ESymbols AttackSymbol = AttackSymbolPointer->ToEnum();

	if (!SelectedUnit->CanAttack() || EnemyUnit->CanDefend(EnemySide, AttackSymbol))
		return false;

	return true;
}

void AGameplayManager::MoveUnit(const FIntPoint& EndCord, int32 Side)
{ 
	SelectedUnit->Rotate(Side);

	EnemyDamage(SelectedUnit);
	if(SelectedUnit == nullptr) return;  // unit was killed

	SelectedUnit->Action();

	AHexGridManager::ChangeUnitPosition(SelectedUnit, EndCord);

	EnemyDamage(SelectedUnit);
	if(SelectedUnit == nullptr) return;  // unit was killed

	SelectedUnit->Action();

}

void AGameplayManager::EnemyDamage(AUnit* Target)
{ // Returns true is Enemy spear can kill the Target
	// TODO: return true if Unit was killed; update in symbols (and in other classes)
	FIntPoint Cord = Target->CurrentCord;
	TArray<AUnit* > Units = AHexGridManager::AdjacentUnits(Cord);
	
	for (int32 side = 0; side < 6; side++) 
	{	
		if (Units[side] && Units[side]->Controller != Target->Controller)
		{	
			int32 EnemySide = AHexGridManager::AdjacentCordSide(side);
			Units[side]->PassiveAction(EnemySide);

			bool bTargetKilled = AHexGridManager::GetUnit(Cord) == nullptr;
			if (bTargetKilled) break;
		}
	}
}

void AGameplayManager::KillUnit(AUnit* Target)
{
	if (Target == SelectedUnit)
		SelectedUnit = nullptr;

	if (Target->Controller == EPlayer::DEFENDER)
	{
		DefenderUnitsAlive--;
	}
	else
	{
		AttackerUnitsAlive--;
	}
	AHexGridManager::RemoveUnit(Target);

	CheckWin();
	
}

void AGameplayManager::CheckWin() {
	if (DefenderUnitsAlive == 0)
		PrintString("Attacker won");
	else if (AttackerUnitsAlive == 0)
		PrintString("Defender won");
}

#pragma endregion


#pragma region Main Functions


void AGameplayManager::InputListener(FIntPoint Cord)
{
	FString output = Cord.ToString();
	PrintString(output);

	if(SelectUnit(Cord) || SelectedUnit == nullptr)
		return; // selected a new unit || wrong input which didn't select any ally unit


	if (UnitsLeftToBeSummoned > 0)  // Summon phase
	{
		/*
		* Units are placed by the players in subsequent order on their chosen "Starting Locations"
		* inside the area of the gameplay board.
		*/
		SummonUnit(Cord);
	}
	else  // Gameplay phase
	{
		Gameplay(Cord);
	}

	SelectedUnit = nullptr;  // IMPORTANT
}


bool AGameplayManager::SelectUnit(const FIntPoint& Cord) {
	/**
	 * Select friendly Unit on a given Cord
	 * 
	 * @return true if unit has been selected in this operation
	 */

	AUnit* NewSelection = AHexGridManager::GetUnit(Cord);
	if (NewSelection && NewSelection->Controller == CurrentPlayer)
	{
		SelectedUnit = NewSelection;
		PrintString("You have selected a Unit");

		return true;
	}

	return false;
}



void AGameplayManager::Gameplay(FIntPoint Cord)
{
	PrintString("Gameplay is working");

	int32 Side;  // Gets Updated with IsLegalMove()
	if (IsLegalMove(Cord, Side))
	{
		MoveUnit(Cord, Side);
		SwitchPlayerTurn();
	}

}


void AGameplayManager::SummonUnit(FIntPoint Cord)
{
	/**
	 * Summon currently selected unit to a Gameplay Board
	 *
	 *
	 * @param Cord cordinate, on which Unit will be summoned
	 */
	

	// check if unit is already summoned
	EHexTileType SelectedUnitTileType = AHexGridManager::GetTileType(SelectedUnit->CurrentCord);  // todo getters/setters

	if (SelectedUnitTileType != EHexTileType::SENTINEL)
	{
		PrintString("This Unit has been already summoned");
		return;
	}


	EHexTileType SelectedHexType = AHexGridManager::GetTileType(Cord);

	bool bSelectedCurrentPlayerSpawn =
		(SelectedHexType == EHexTileType::ATTACKER_SPAWN && CurrentPlayer == EPlayer::ATTACKER) ||
		(SelectedHexType == EHexTileType::DEFENDER_SPAWN && CurrentPlayer == EPlayer::DEFENDER);

	if (!bSelectedCurrentPlayerSpawn)
	{
		PrintString("Thats a wrong summon location");  // TODO: Don't reset SelectedUnit
		return;
	}

	PrintString("You summoned a Unit");

	// TeleportUnit(Cord);
	AHexGridManager::ChangeUnitPosition(SelectedUnit, Cord);

	if (CurrentPlayer == EPlayer::ATTACKER)  // TODO: Move to setup
		SelectedUnit->Rotate(0);
	else
		SelectedUnit->Rotate(3);


	SwitchPlayerTurn();

	UnitsLeftToBeSummoned--;
}
#pragma endregion

#pragma region Tests





#pragma endregion



#pragma region GameSetup

void AGameplayManager::GameSetup()
{
	AttackerUnitsAlive = AHexGridManager::AttackerUnits.Num();
	DefenderUnitsAlive = AHexGridManager::DefenderUnits.Num();

	UnitsLeftToBeSummoned = AttackerUnitsAlive + DefenderUnitsAlive;

	CurrentPlayer = EPlayer::ATTACKER;
}






/*
void AGameplayManager::TimerFunction()
{
	CallTracker--;
	if (CallTracker == 0)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		SimpleAutomaticTests();
	}
}
*/

void AGameplayManager::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// UnitsLeftToBeSummoned = AttackerUnitsAlive + DefenderUnitsAlive;  // Flag that manages the state of the game
}


void AGameplayManager::BeginPlay()
{
	
	

}


AGameplayManager::AGameplayManager()
{
	
}

#pragma endregion