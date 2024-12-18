// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GobboShopSim : ModuleRules
{
	public GobboShopSim(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG" });

        PublicDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
    }
}
