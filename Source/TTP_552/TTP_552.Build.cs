// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TTP_552 : ModuleRules
{
	public TTP_552(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "ToolMenus", 
			"Slate", "SlateCore", "UnrealEd", "LevelSequence", "SequencerScripting", "SequencerScriptingEditor", 
			"LevelSequenceEditor"
		});
	}
}
