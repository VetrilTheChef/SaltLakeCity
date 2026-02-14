// SaltLakeCity 5.7

using UnrealBuildTool;
using System.Collections.Generic;

public class SaltLakeCityEditorTarget : TargetRules
{
	public SaltLakeCityEditorTarget(TargetInfo Target) : base(Target)
    {
        bOverrideBuildEnvironment = true;
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V6;
        IncludeOrderVersion  = EngineIncludeOrderVersion.Latest;
        CppStandard = CppStandardVersion.Cpp20;

        ExtraModuleNames.AddRange( new string[] { "SaltLakeCity" } );
	}
}
