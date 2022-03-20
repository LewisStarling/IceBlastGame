// Copyright Epic Games, Inc. All Rights Reserved.

#include "IceBlastGameGameMode.h"
#include "IceBlastGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AIceBlastGameGameMode::AIceBlastGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
