// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MultiMower : ModuleRules
{
	public MultiMower(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
