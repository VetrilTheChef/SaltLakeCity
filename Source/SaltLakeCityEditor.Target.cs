// SaltLakeCity 4.26

using UnrealBuildTool;
using System.Collections.Generic;

public class SaltLakeCityEditorTarget : TargetRules
{
	public SaltLakeCityEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V2;

        ExtraModuleNames.AddRange( new string[] { "SaltLakeCity" } );
	}
}
