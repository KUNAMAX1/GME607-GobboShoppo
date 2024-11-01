// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GobboShopSimHUD.generated.h"

UCLASS()
class AGobboShopSimHUD : public AHUD
{
	GENERATED_BODY()

public:
	AGobboShopSimHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

