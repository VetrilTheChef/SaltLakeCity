// SaltLakeCity 5.7

using UnrealBuildTool;
using System.Collections.Generic;

public class SaltLakeCityTarget : TargetRules
{
	public SaltLakeCityTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V6;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

        ExtraModuleNames.AddRange( new string[] { "SaltLakeCity" } );
	}
}
