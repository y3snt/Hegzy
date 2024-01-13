// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "GameplayEnums.h"
//#include "GameplayConstants.h"
//#include "HexGridManager.h"

#include "Symbol.h"

//#include "HegzyEvents.h"

//#include "HegzEvent.cpp" //aa


//#include "C:/Users/tomek/Documents/GitHub/CPP/Heksy   /Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSpriteComponent.h”

#include "Unit.generated.h"



class UStaticMeshComponent;

class UPaperSpriteComponent;

UCLASS()
class HEKSY_API AUnit : public APawn
{
	GENERATED_BODY()

public:

	TArray<FIntPoint> Directions = {
			FIntPoint(1, 0),
			FIntPoint(0, 1),
			FIntPoint(-1, 1),
			FIntPoint(-1, 0),
			FIntPoint(0, -1),
			FIntPoint(1, -1) };


	// Sets default values for this pawn's properties
	AUnit();
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "UNIT|Statistics")
	FIntPoint CurrentCord;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "UNIT|Statistics")
	int32 CurrentRotation;

	EPlayer Controller;

	//TODO add some kind of refference or TAG to set which team unit is a member of
	FIntPoint Neighbour(int32 Direction);
	//void SetCurrentCord(const FIntPoint& Cord);

	void Move(const FIntPoint& EndCord);

	


protected:
#pragma region UnitSymbols

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UNIT|Statistics")
	TArray<ASymbol*> Symbols;

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

//	static FIntPoint Direction(int32 Side); //TODO think about how to make it static

	static FIntPoint Direction(int32 Side)
	{
		TArray<FIntPoint> Directions = {
			FIntPoint(1, 0),
			FIntPoint(0, 1),
			FIntPoint(-1, 1),
			FIntPoint(-1, 0),
			FIntPoint(0, -1),
			FIntPoint(1, -1) };
		return Directions[Side];
	}

	static int32 DirectionToSide(FIntPoint Direction)  // TODO: MOVE THIS SOMEWHERE
	{
		
		TArray<FIntPoint> Directions = {
			FIntPoint(1, 0),
			FIntPoint(0, 1),
			FIntPoint(-1, 1),
			FIntPoint(-1, 0),
			FIntPoint(0, -1),
			FIntPoint(1, -1) };
			
		//int32 Index;
		//directions.Find(TEXT("Hello"), Index)

		//return Index;
		return Directions.IndexOfByKey(Direction);
	}

	
	void Rotate(int32 Side);
	


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
