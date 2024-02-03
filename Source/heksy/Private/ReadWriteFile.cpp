/*****************************************************************//**
 * \file   ReadWriteFile.cpp
 * \brief  
 * 
 *********************************************************************/

#include "ReadWriteFile.h"
#include "GameplayManager.h"



void UReadWriteFile::InputConnectListener(FIntPoint Cord, bool& bOutSuccess, FString& OutInfoMessage)
{
    
    AGameplayManager::InputListener(Cord);
    
    bOutSuccess = true;
    OutInfoMessage = FString::Printf(TEXT("Pass Cord To Gameplay Manager Succeeded"));
}
