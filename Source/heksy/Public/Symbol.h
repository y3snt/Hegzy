/*****************************************************************//**
 * \file   Symbol.h
 * \brief  Partent class of gameplay symbols
 * 
 *********************************************************************/
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
	ASymbol();
	virtual ESymbols ToEnum();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tile")
	UStaticMeshComponent *TileMesh;  // U: visible mesh

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetSymbolEnum(ESymbols Symbol);
	
private:
	ESymbols SymbolEnum;

};