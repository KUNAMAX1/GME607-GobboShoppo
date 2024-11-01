// Copyright Epic Games, Inc. All Rights Reserved.

#include "GobboShopSimGameMode.h"
#include "GobboShopSimHUD.h"
#include "GobboShopSimCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGobboShopSimGameMode::AGobboShopSimGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AGobboShopSimHUD::StaticClass();
}
