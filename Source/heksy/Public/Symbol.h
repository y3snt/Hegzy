// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Symbol.generated.h"

UCLASS()
class HEKSY_API ASymbol : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASymbol();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};

// Action.h
#include "Action.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UAction : public UInterface
{
    GENERATED_BODY()
};

class IAction
{    
    GENERATED_BODY()

public:
    virtual void Action(AUnit* Unit, int32 Side);  // == 0 ?
};

// Action.h
#include "Action.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UPassiveAction : public UInterface
{
    GENERATED_BODY()
};

class IPassiveAction
{    
    GENERATED_BODY()

public:
    virtual void PassiveAction(AUnit* Unit, int32 Side);  // == 0 ?
};

// Sword.h
UCLASS(Blueprintable, Category="MyGame")
class ASword : public AActor, public IAction
{
    GENERATED_BODY()

public:
    /** Add interface function overrides here. */
	virtual void Action(AUnit* Unit, int32 Side) override;
}

// Sword.cpp
void ASword::Action(AUnit* Unit, int32 Side) // Adjacent Attack
{
	AUnit* Target = GridManager->GetAdjacentUnit(Unit->CurrentCord, Side);
	if (Target && Target->Controller != Unit->Controller)
		Target->Damage(Side);
}

// Spear.h
UCLASS(Blueprintable, Category="MyGame")
class ASpear : public AActor, public IAction, public IPassiveAction
{
    GENERATED_BODY()

public:
    /** Add interface function overrides here. */
	virtual void Action(AUnit* Unit, int32 Side) override;
	virtual void PassiveAction(AUnit* Unit, int32 Side) override;
}

// Spear.cpp
void ASpear::Action(AUnit* Unit, int32 Side)
{
	AUnit* Target = GridManager->GetAdjacentUnit(Unit->CurrentCord, Side);
	if (Target && Target->Controller != Unit->Controller)
		Target->Damage(Side);
}

void ASpear::PassiveAction(AUnit* Unit, int32 Side)
{
	AUnit* Target = GridManager->GetAdjacentUnit(Unit->CurrentCord, Side);
	if (Target && Target->Controller != Unit->Controller)
		Target->Damage(Side);
}



// Bow.h
UCLASS(Blueprintable, Category="MyGame")
class ABow : public AActor, public IAction
{
    GENERATED_BODY()

public:
    /** Add interface function overrides here. */
	virtual void Action(AUnit* Unit, int32 Side) override;
}

// Bow.cpp
void ABow::Action(AUnit* Unit, int32 Side)
{
	AUnit* Target = GridManager->GetShotTarget(Unit->CurrentCord, Side);
	if (Target && Target->Controller != Unit->Controller)
		Target->Damage(Side);
}


// Push.h
UCLASS(Blueprintable, Category="MyGame")
class APush : public AActor, public IAction
{
    GENERATED_BODY()

public:
    /** Add interface function overrides here. */
	virtual void Action(AUnit* Unit, int32 Side) override;
}

// Push.cpp
void APush::Action(AUnit* Unit, int32 Side) // Adjacent Attack
{
	AUnit* Target = GridManager->GetAdjacentUnit(Unit->CurrentCord, Side);
	if(!Target || Target->Controller == Unit->Controller)
		return;

	EHexTileType BehindTile = GridManager->GetDistantTileType(Unit->CurrentCord, side, 2);
	AUnit* BehindUnit = GridManager->GetDistantUnit(Unit->CurrentCord, side, 2);

	// TODO: Move to hex grid MG (which will validate position and kill if on a bad position)
	if (BehindUnit != nullptr || BehindTile == EHexTileType::SENTINEL)  // Pushing outside the map or in the Unit
	{
		KillUnit(Target);
	}
	else if (BehindUnit == nullptr) // Simple push TODO: we don't need else if here, just else
	{
		GridManager->ChangeUnitPosition(Target, GridManager->GetDistantCord(Unit->CurrentCord, side, 2));
		if (EnemyDamage(Target))  // TODO: should be passive
			KillUnit(Target);
	}
}