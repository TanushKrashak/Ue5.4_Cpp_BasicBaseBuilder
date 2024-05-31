// Copyright Epic Games, Inc. All Rights Reserved.

#include "Cpp_BasicBaseBuilderGameMode.h"
#include "Cpp_BasicBaseBuilderCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACpp_BasicBaseBuilderGameMode::ACpp_BasicBaseBuilderGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
