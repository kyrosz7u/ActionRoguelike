// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ActionRoguelikeEditorTarget : TargetRules
{
	public ActionRoguelikeEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "ActionRoguelike" } );
		// https://forums.unrealengine.com/t/dealing-with-ue-4-27-build-errors-after-upgrading-to-macos-ventura-13-3-1/1134042
		if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			bOverrideBuildEnvironment = true;
			AdditionalCompilerArguments = "-Wno-unused-but-set-variable";
		}
	}
}
