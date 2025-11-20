// Fill out your copyright notice in the Description page of Project Settings.


#include "StealthGameMode.h"

void AStealthGameMode::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	// 1. To print screen
	// Display a debug message for five seconds.
	// the -1 "Key" value argument pervents the message from being updated or refreshed.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is StealthGameModeBase! This is hybrid Build"));

	// 2. To print console
	UE_LOG(LogTemp, Warning, TEXT("Hello World"));

	// 3. Priting Values to console
	int TestNumber = 10;
	float TestFloat = 30.0f;
	bool TestBool = false;
	UE_LOG(LogTemp, Warning, TEXT("TestNumber: %i"), TestNumber, TestFloat, TestBool);

	int* NumPointer = &TestNumber;
	UE_LOG(LogTemp, Warning, TEXT("NumPointer: % i"), NumPointer);
	UE_LOG(LogTemp, Warning, TEXT("NumPointer: % i"), *NumPointer);

	// 4. Modern way of debugging values
	//UE_LOGFMT(LogTemp, Warning, "TestNumber: {0}, TestFloat: {1}, TestBool:{2}", TestNumber, TestFloat, "Name");
}