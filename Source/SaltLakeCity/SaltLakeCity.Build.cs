// SaltLakeCity 5.7

using UnrealBuildTool;

public class SaltLakeCity : ModuleRules
{
	public SaltLakeCity(ReadOnlyTargetRules Target) : base(Target)
	{
        CppStandard = CppStandardVersion.Default;
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        //PrivatePCHHeaderFile = "SaltLakeCityPCH.h";

        PrivateDependencyModuleNames.AddRange(new string[]
            {
                "AIModule",
                "AssetRegistry",
                "Core",
                "CoreUObject",
                "Engine",
                "Foliage",
                "GameplayAbilities",
                "GameplayTags",
                "GameplayTasks",
                "InputCore",
                "Landscape",
                "RenderCore",
                "RHI",
                "Slate",
                "SlateCore",
                "StructUtils",
                "UMG"
            }
        );

        PrivateIncludePaths.Add("SaltLakeCity/");

        PublicDependencyModuleNames.AddRange(new string[]
            {
                "Core",
                "CoreUObject",
                "Engine"
            }
        );

        if (Target.Type == TargetType.Editor)
        {
            PrivateDependencyModuleNames.Add("UnrealEd");
        }

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
