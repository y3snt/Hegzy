// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameSetupManager.generated.h"

/**
 * Before players start a new game, they have to specify which faction starts first (is attacker) and their names.
 * Otherwise the default names will be chosen.
 * 
 * Then a new file is created
 * 
 */

struct PlayerData
{
	FString Name;
	FString Faction;

	FString Color;

	int32 TeamId;			// 

	FString ControllerType;	// Who controlls the player HotSeat/AI/Multiplayer
};


UCLASS()
class HEKSY_API UGameSetupManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	 * Open a text file and read its content
	 *
	 * @param PlayerNames		List of Players names
	 * @param Factions			Factions in their initiative order
	 * @param bOutSuccess		If the action was a success or not
	 * @param OutInfoMessage	More information about the action's result
	 *
	 * @return The string content of your file
	 */

	//UFUNCTION(BlueprintCallable, Category = "test|1 - Read Write File")
	//static FString StartNewGame(TArray<PlayerData> Players, bool& bOutSuccess, FString& OutInfoMessage);


	/**
	 * Create a text file with your content
	 *
	 * @param FilePath			The path of your file
	 * @param String			The string you want to write in your file
	 * @param bOutSuccess		If the action was a success or not
	 * @param OutInfoMessage	More information about the action's result
	 *
	 * @return The string content of your file
	 */


	//UFUNCTION(BlueprintCallable, Category = "test|1 - Read Write File")
	//static void WriteStringToFile(FString FilePath, FString String, bool& bOutSuccess, FString& OutInfoMessage);
};
