// Copyright Epic Games, Inc. All Rights Reserved.

#include "TTP_552GameMode.h"
#include "TTP_552Character.h"
#include "UObject/ConstructorHelpers.h"

ATTP_552GameMode::ATTP_552GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
