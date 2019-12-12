// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UE4StateMachineGameMode.h"
#include "UE4StateMachinePlayerController.h"
#include "UE4StateMachineCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE4StateMachineGameMode::AUE4StateMachineGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AUE4StateMachinePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}