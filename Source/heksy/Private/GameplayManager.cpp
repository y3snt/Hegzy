// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayManager.h"

AGameplayManager::AGameplayManager()
{

}


void AGameplayManager::InputListener(FIntPoint Cord)
{

	FString output = Cord.ToString();
	if (GEngine) // prints stuff to screen
		GEngine->AddOnScreenDebugMessage(-1, 15.0f,
			FColor::Yellow, output, true);
}


void AGameplayManager::SpawnUnits()
{
	if (AttackerUnits.Num() > GridManager->AttackerTiles.Num() || DefenderUnits.Num() > GridManager->DefenderTiles.Num())
	{
		if (GEngine) // prints stuff to screen
			GEngine->AddOnScreenDebugMessage(-1, 15.0f,
				FColor::Yellow, FString::Printf(TEXT("AGameplayManager::SpawnUnits() Board is too small for that number of units")), true);
		return;
	}
	for (int32 i = 0; i < AttackerUnits.Num(); i++)
	{
		FIntPoint TI = GridManager->AttackerTiles[i]->TileIndex;


		//TI += AttackerUnits[0]->Neighbours(3);
		AttackerUnits[i]->TileIndex = TI;

		AttackerUnits[i]->SetActorLocation(GridManager->HexGrid2DArray[TI.X][TI.Y]->GetActorLocation());
	}
	/*
	for (int32 i = 0; i < DefenderUnits.Num(); i++)
	{
		

		TI = DefenderUnits[i]->TileIndex;
		DefenderUnits[i]->TileIndex = TI; GridManager->DefenderTiles[i]->TileIndex + DefenderUnits[0]->Neighbours(0);
		
		DefenderUnits[i]->SetActorLocation(GridManager->HexGrid2DArray[TI.X][TI.Y]->GetActorLocation());
	}
	*/
}


void AGameplayManager::SetupGame()
{
	SpawnUnits();
	//GridManager->GenerateGrid();
}

#define PrintString(String)

void AGameplayManager::TimerFunction()
{
	CallTracker--;
	if (CallTracker == 0)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		SetupGame();
	}
}

void AGameplayManager::BeginPlay()
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AGameplayManager::TimerFunction, 1.0f, true, 0.5f);
	
}