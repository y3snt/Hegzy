// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayHandler.h"
#include <Kismet/GameplayStatics.h>
#include "EngineUtils.h"
#include "Engine.h"



#define PrintString(String) GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::White, String)


//UGameplayHandler::UGameplayHandler() { }

void UGameplayHandler::helloworld()
{
	PrintString("hello world");
	if (AutomaticTest == nullptr)
	{

	}
	if (AutomaticTest == EAutomaticTestsList::INVALID)
	{
		PrintString("invalid");
	}
	else if (AutomaticTest == EAutomaticTestsList::BASIC_UNIT_SETUP)
	{
		PrintString("BASIC_UNIT_SETUP");
	}
	else if (AutomaticTest == EAutomaticTestsList::EMPTY)
	{
		PrintString("EMPTY");
	}
}

template<typename T>
void FindAllActors(UWorld* World, TArray<T>& Out)
{
	for (TActorIterator<T> It(World); It; ++It)
	{
		Out.Add(It);
	}
}



void UGameplayHandler::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);



	TArray<AUnit> Boxes;

	//FindAllActors<AUnit>(GetWorld(), Boxes);

	/*
	for (TActorIterator<AUnit> It(GetWorld()); It; ++It)
	{
		if (AUnit* Unit = Cast<AUnit>(*It))
		{
			PrintString("oke");
		}
	}
	*/
	
	/*
	for (AUnit actor : Boxes)
	{
		/*
		if (GEngine) // prints stuff to screen
			GEngine->AddOnScreenDebugMessage(-1, 15.0f,
				FColor::Yellow, actor->GetTransform().ToString());*/
	//}

}

void UGameplayHandler::Deinitialize()
{
}
