// Copyright Epic Games, Inc. All Rights Reserved.

#include "MultiMowerGameMode.h"
#include "MultiMowerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMultiMowerGameMode::AMultiMowerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
