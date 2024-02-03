#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "GameplayEnums.h"

#include "Unit.generated.h"

class ASymbol;
class UStaticMeshComponent;

UCLASS()
class HEKSY_API AUnit : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UNIT|Model")
	UStaticMeshComponent *UnitMesh;  // visible mesh

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "UNIT|Statistics")
	int32 CurrentRotation;

	UPROPERTY(EditAnywhere, Category = "UNIT|Statistics")
	TArray<ASymbol*> Symbols;

	/* Called when the game starts or when spawned */
	virtual void BeginPlay() override;

public:	
	EPlayer Controller;  // who owns the Unit

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "UNIT|Statistics")
	FIntPoint CurrentCord;  // on which cord Unit is currently placed

	AUnit();

	/* Called to bind functionality to input */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	/**
	 * Rotate the unit towards Side
	 * 
	 * @param Side {0, 1, ..., 5}
	 * @note this is an absolute rotation (not based on current rotation of the unit)
	 */
	void Rotate(int32 Side);

	/**
	 * Get the Symbol on a given Side of Unit
	 * 
	 * @param side absolute side of a hex tile
	 * @return ASymbol* 
	 * 
	 * @note converts absolute hex side to loacal unit side (applying unit rotation)
	 */
	ASymbol* GetSymbol(int32 Side);

	/**
	 * Get Symbol on a front of the Unit
	 * 
	 * @return ESymbols
	 */
	ASymbol* GetFrontSymbol();

	/**
	 * Return true if Unit can block action from given Side
	 * 
	 * @param Side of a Unit, from which it could perform a block
	 * @param AttackerSymbol 
	 * @return true if Unit can block AttackerSymbol
	 * @return false otherwise
	 */
	bool CanDefend(int32 Side, ESymbols AttackerSymbol = ESymbols::INVALID);

	/**
	 * Return true if Unit can perform an attack from the front side
	 * 
	 * @return true if can attack
	 * @note returns true if action performed by the Unit can kill or move an enemy
	 */
	bool CanAttack();

	/**
	 * Take damage from AttackSide, if cannot defend - dies
	 * 
	 * @param AttackSide 
	 * @param AttackerSymbol 
	 */
	void Damage(int32 AttackSide, ESymbols AttackerSymbol = ESymbols::INVALID);

	/**
	 * Perform Actions of all Symbols that belongs to the unit
	 */
	void Action();

	/**
	 * Perform PassiveAction of a Symbol on given side of the Unit
	 * 
	 * @param Side 
	 * @note if there is no Passive Symbol on the Side, no action is performed
	 */
	void PassiveAction(int32 Side);

};
