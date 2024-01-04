// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Symbol.h"


//#include "C:/Users/tomek/Documents/GitHub/CPP/Heksy   /Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSpriteComponent.h”

#include "Unit.generated.h"


class UStaticMeshComponent;

class UPaperSpriteComponent;

UCLASS()
class HEKSY_API AUnit : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AUnit();

	//TODO add some kind of refference or TAG to set which team unit is a member of

protected:
#pragma region UnitSymbols
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UNIT|Statistics")  // U: property, that will be visible in the editor
		TSubclassOf <ASymbol> FrontSymbol;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UNIT|Statistics")
	TSubclassOf<ASymbol> FrontRightSymbol;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UNIT|Statistics")
	TSubclassOf<ASymbol> FrontLeftSymbol;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UNIT|Statistics")  // U: property, that will be visible in the editor
		TSubclassOf<ASymbol> BackSymbol;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UNIT|Statistics")
	TSubclassOf<ASymbol> BackRightSymbol;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UNIT|Statistics")
	TSubclassOf<ASymbol> BackLeftSymbol;

#pragma endregion


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UNIT|Model")
	UStaticMeshComponent *UnitMesh;  // U: visible mesh

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UNIT|Model")
	//UPaperSpriteComponent *UnitSprite;  // U: visible mesh


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
