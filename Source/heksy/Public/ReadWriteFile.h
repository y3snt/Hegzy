/*****************************************************************//**
 * \file   ReadWriteFile.h
 * \brief  Main Input Handler
 * 
 *********************************************************************/

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
	 * GameplayManager:InputListener caller that passes Coordinates from the player mouse Input.
	 * 
	 * @param Cord
	 * @param bOutSuccess
	 * @param OutInfoMessage
	 */
	UFUNCTION(BlueprintCallable, Category = "test|1 - Read Write File")
	static void InputConnectListener(FIntPoint Cord, bool& bOutSuccess, FString& OutInfoMessage);


	
};
