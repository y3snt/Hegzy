// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "ReadWriteFile.generated.h"



/**
 * 
 */
UCLASS()
class HEKSY_API UReadWriteFile : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Open a text file and read its content
	 *
	 * @param FilePath			The path of your file
	 * @param bOutSuccess		If the action was a success or not
	 * @param OutInfoMessage	More information about the action's result
	 *
	 * @return The string content of your file
	 */
	UFUNCTION(BlueprintCallable, Category = "test|1 - Read Write File")
	static FString ReadStringFromFile(FString FilePath, bool& bOutSuccess, FString& OutInfoMessage);


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
	UFUNCTION(BlueprintCallable, Category = "test|1 - Read Write File")
	static void WriteStringToFile(FString FilePath, FString String, bool& bOutSuccess, FString& OutInfoMessage);



	
	UFUNCTION(BlueprintCallable, Category = "test|1 - Read Write File")
	static void InputConnectListener(FIntPoint Cord, UGameplayHandler* Handler, bool& bOutSuccess, FString& OutInfoMessage);


	
};
