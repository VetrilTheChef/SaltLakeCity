// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Commands/GameModes/BBGameModeCommand.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "GameModes/BBGameModeStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBGameModeCommandSpec, "SaltLakeCity.Commands.GUI.GameModeCommand", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	ABBGameModeStub * GameMode = nullptr;

	UPROPERTY()
	TArray<UClass *> CommandClasses;

	// SUT
	UPROPERTY()
	UBBGameModeCommand * Command = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBGameModeCommandSpec)

void UBBGameModeCommandSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBGameModeCommand>(FString(TEXT("/Game/Commands/GUI")), CommandClasses);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		GameMode = TestWorld->SpawnActor<ABBGameModeStub>(ABBGameModeStub::StaticClass(), SpawnParameters);

		UTEST_TRUE("Game Mode is valid", IsValid(GameMode))

		return true;
	});

	AfterEach([this]()
	{
		Command = nullptr;

		TestWorld->DestroyActor(GameMode);

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & CommandClass : CommandClasses)
	{
		Describe("[" + CommandClass->GetName() + "]", [this, CommandClass]()
		{
			It("Given a new game mode state, expect the command to set it upon execution", [this, CommandClass]()
			{
				Command = NewObject<UBBGameModeCommand>(TestWorld, CommandClass);

				UTEST_TRUE("Command is valid", IsValid(Command))

				TArray<EBBGameMode> GameModes;
				GameModes.Empty();
				GameModes.Emplace(EBBGameMode::Play);
				GameModes.Emplace(EBBGameMode::None);
				GameModes.Emplace(EBBGameMode::Build);
				GameModes.Emplace(EBBGameMode::Play);
				GameModes.Emplace(EBBGameMode::Build);

				Command->SetGameMode(GameMode);

				for (int Index = 0; Index < 5; Index++)
				{
					Command->SetActiveGameMode(GameModes[Index]);

					Command->Execute();

					TEST_TRUE(GameMode->GetMode() == GameModes[Index])
				}

				return true;
			});
		});
	}
}