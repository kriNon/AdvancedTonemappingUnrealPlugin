// Copyright Epic Games, Inc. All Rights Reserved.
using UnrealBuildTool;

public class AdvancedTonemapping : ModuleRules
{
	public AdvancedTonemapping(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] {"Core", "Projects", "RenderCore", "Engine", "UnrealShaderModLoader"});
	}
}