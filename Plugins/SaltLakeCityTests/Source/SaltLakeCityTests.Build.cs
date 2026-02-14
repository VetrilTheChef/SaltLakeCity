using UnrealBuildTool;

public class SaltLakeCityTests : ModuleRules
{
    public SaltLakeCityTests(ReadOnlyTargetRules Target) : base(Target)
    {
        CppStandard = CppStandardVersion.Default;
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivatePCHHeaderFile = "SaltLakeCityTestsPCH.h";
        MinFilesUsingPrecompiledHeaderOverride = 1;
        bUseUnity = false;

        PrivateDependencyModuleNames.AddRange(new string[]
            {
                "AutomationDriver",
                "AIModule",
                "Core",
                "CoreUObject",
                "Engine",
                "GameplayAbilities",
                "GameplayTags",
                "GameplayTasks",
                "InputCore",
                "Landscape",
                "LandscapeEditor",
                "LandscapeEditorUtilities",
                "RenderCore",
                "SlateCore",
                "UMG",
                "UnrealEd",
                "SaltLakeCity"
            }
        );

        PrivateIncludePaths.Add("../../../Source/SaltLakeCity/");

        PublicDependencyModuleNames.AddRange(new string[]
            {
                "AutomationDriver",
                "AIModule",
                "Core",
                "CoreUObject",
                "Engine",
                "GameplayAbilities",
                "GameplayTags",
                "GameplayTasks",
                "InputCore",
                "Landscape",
                "LandscapeEditor",
                "LandscapeEditorUtilities",
                "RenderCore",
                "SlateCore",
                "UMG",
                "UnrealEd",
                "SaltLakeCity"
            }
        );

        PrivateIncludePaths.Add("../../../Source/SaltLakeCity/");
    }
}