#include "Unit.h"
#include "GameplayManager.h"
#include "HexGridManager.h"
#include "Symbol.h"

void AUnit::BeginPlay()
{
	Super::BeginPlay();
}

AUnit::AUnit()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));  // "container" for other components
	UnitMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UnitMesh"));
	UnitMesh->SetupAttachment(RootComponent);  // attach component to the root / container

	CurrentRotation = 0;
}

void AUnit::Rotate(int32 Side)
{
	CurrentRotation = Side;
	
	// 360 / 6 = 60 -> degrees needed to rotate unit
	// "Direction + 4" Accounts for global rotation setting for objects in the level
	int32 GridRotation = 4;
	this->SetActorRotation(FRotator(0, 60 * (Side + GridRotation), 0), ETeleportType::TeleportPhysics);
}

void AUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {}

ASymbol* AUnit::GetFrontSymbol()
{ 
	return Symbols[0];
}

ASymbol* AUnit::GetSymbol(int32 Side)
{ 
	return Symbols[(Side - CurrentRotation + 6) % 6];
}

bool AUnit::CanAttack()
{
	IAction* Symbol = Cast<IAction>(GetFrontSymbol());

	if(Symbol)  // currently all action symbols can attack
		return true;
	
	return false;
}


bool AUnit::CanDefend(int32 Side, ESymbols AttackerSymbol)
{
	if(!GetSymbol(Side)) return false;
	
	ESymbols Symbol = GetSymbol(Side)->ToEnum();
	if (Symbol == ESymbols::SHIELD && AttackerSymbol != ESymbols::PUSH)  // Does Unit have a shield?
		return true;
	
	return false;
}

void AUnit::Damage(int32 AttackSide, ESymbols AttackerSymbol) 
{
	int32 UnitSide = AHexGridManager::AdjacentCordSide(AttackSide); 
	if(!CanDefend(UnitSide, AttackerSymbol)) {
		AGameplayManager::KillUnit(this);
	}

}

void AUnit::Action()
{
	for (int32 side = 0; side < 6; side++)
	{
		IAction* Symbol = Cast<IAction>(GetSymbol(side));

		if(Symbol)
			Symbol->Action(this, side);

	}
}

void AUnit::PassiveAction(int32 Side)
{
	IPassiveAction* Symbol = Cast<IPassiveAction>(GetSymbol(Side));

	if(Symbol)
		Symbol->PassiveAction(this, Side);
}