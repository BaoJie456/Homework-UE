// Copyright Epic Games, Inc. All Rights Reserved.

#include "Learn01GameMode.h"
#include "Learn01Character.h"
#include "UObject/ConstructorHelpers.h"

ALearn01GameMode::ALearn01GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
