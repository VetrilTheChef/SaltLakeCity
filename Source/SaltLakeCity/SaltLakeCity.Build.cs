// SaltLakeCity 4.26

using UnrealBuildTool;

public class SaltLakeCity : ModuleRules
{
	public SaltLakeCity(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivatePCHHeaderFile = "SaltLakeCityPCH.h";
        MinFilesUsingPrecompiledHeaderOverride = 1;
        bUseUnity = false;

        PrivateDependencyModuleNames.AddRange(new string[]
            {
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
                "UMG",
                "UnrealEd"
            }
        );

        PrivateIncludePaths.Add("SaltLakeCity/");

        PublicDependencyModuleNames.AddRange(new string[]
            {
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
                "UMG",
                "UnrealEd"
            }
        );

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
