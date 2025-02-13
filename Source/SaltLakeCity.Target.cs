// SaltLakeCity 4.26

using UnrealBuildTool;
using System.Collections.Generic;

public class SaltLakeCityTarget : TargetRules
{
	public SaltLakeCityTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V2;

        ExtraModuleNames.AddRange( new string[] { "SaltLakeCity" } );
	}
}
