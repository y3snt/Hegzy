// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Unit.h"
#include "Action.h"
#include "PassiveAction.h"

#include "Symbol.generated.h"

//class AUnit;

class UStaticMeshComponent;

UCLASS()
class HEKSY_API ASymbol : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASymbol();
	virtual ESymbols ToEnum();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	ESymbols SymbolEnum = ESymbols::INVALID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tile")
	UStaticMeshComponent *TileMesh;  // U: visible mesh

	// TODO: protected constructor

};


// Sword.h
/*
UCLASS(Blueprintable, Category = "MyGame")
class ASword : public ASymbol, public IAction
{
	GENERATED_BODY()

public:
	virtual void Action(AUnit* Unit, int32 Side) override;
};
// Sword.cpp
void ASword::Action(AUnit* Unit, int32 Side) // Adjacent Attack
{

	AUnit* Target = AHexGridManager::GetUnit(AHexGridManager::AdjacentCord(Unit->CurrentCord, Side));
	if (Target && Target->Controller != Unit->Controller)
		Target->Damage(Side, this->ToEnum());
}


// Spear.h
UCLASS(Blueprintable, Category = "MyGame")
class ASpear : public ASymbol, public IAction, public IPassiveAction
{
	GENERATED_BODY()

public:
	virtual void Action(AUnit* Unit, int32 Side) override;
	virtual void PassiveAction(AUnit* Unit, int32 Side) override;
};

// Spear.cpp
void ASpear::Action(AUnit* Unit, int32 Side)
{
	AUnit* Target = AHexGridManager::GetUnit(AHexGridManager::AdjacentCord(Unit->CurrentCord, Side));
	if (Target && Target->Controller != Unit->Controller)
		Target->Damage(Side, this->ToEnum());
}

void ASpear::PassiveAction(AUnit* Unit, int32 Side)
{
	AUnit* Target = AHexGridManager::GetUnit(AHexGridManager::AdjacentCord(Unit->CurrentCord, Side));
	if (Target && Target->Controller != Unit->Controller)
		Target->Damage(Side, this->ToEnum());
}



// Bow.h
UCLASS(Blueprintable, Category = "MyGame")
class ABow : public ASymbol, public IAction
{
	GENERATED_BODY()

public:
	virtual void Action(AUnit* Unit, int32 Side) override;
};

// Bow.cpp
void ABow::Action(AUnit* Unit, int32 Side)
{
	AUnit* Target = AHexGridManager::GetShotTarget(Unit->CurrentCord, Side);
	if (Target && Target->Controller != Unit->Controller)
		Target->Damage(Side, this->ToEnum());
}


// Push.h
UCLASS(Blueprintable, Category = "MyGame")
class APush : public ASymbol, public IAction
{
	GENERATED_BODY()

public:
	virtual void Action(AUnit* Unit, int32 Side) override;
};

// Push.cpp
void APush::Action(AUnit* Unit, int32 Side) // Adjacent Attack
{
	AUnit* Target = AHexGridManager::GetUnit(AHexGridManager::AdjacentCord(Unit->CurrentCord, Side));
	if (!Target || Target->Controller == Unit->Controller)
		return;

	EHexTileType BehindTile = AHexGridManager::GetDistantTileType(Unit->CurrentCord, Side, 2);
	AUnit* BehindUnit = AHexGridManager::GetDistantUnit(Unit->CurrentCord, Side, 2);

	// TODO: Move to hex grid MG (which will validate position and kill if on a bad position)
	if (BehindUnit || BehindTile == EHexTileType::SENTINEL)  // Pushing outside the map or in the Unit
	{
		AGameplayManager::KillUnit(Target);
	}
	else if (BehindUnit == nullptr) // Simple push TODO: we don't need else if here, just else
	{
		AHexGridManager::ChangeUnitPosition(Target, AHexGridManager::GetDistantCord(Unit->CurrentCord, Side, 2));
		AGameplayManager::EnemyDamage(Target);
	}
}
*/