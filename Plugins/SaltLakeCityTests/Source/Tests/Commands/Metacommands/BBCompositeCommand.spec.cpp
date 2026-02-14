// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Commands/Controllers/BBPauseCommandStub.h"
#include "Commands/Metacommands/BBCompositeCommand.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBCompositeCommandSpec,
	"SaltLakeCity.Commands.Metacommands.CompositeCommand",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	TArray<UClass *> CommandClasses;

	// SUT
	UPROPERTY()
	UBBCompositeCommand * Command = nullptr;

END_DEFINE_SPEC(UBBCompositeCommandSpec)

void UBBCompositeCommandSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBCompositeCommand>(FString(TEXT("/Game/Commands/Metacommands")), CommandClasses);

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		return true;
	});

	AfterEach([this]()
	{
		Command = nullptr;

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & CommandClass : CommandClasses)
	{
		Describe("[" + CommandClass->GetName() + "]", [this, CommandClass]()
		{
			It("Given a new set of children commands, expect the command to execute them upon execution", [this, CommandClass]()
			{
				Command = NewObject<UBBCompositeCommand>(TestWorld, CommandClass);

				UTEST_TRUE("Command is valid", IsValid(Command))

				TArray<UBBPauseCommandStub *> PauseCommands;
				PauseCommands.Empty();
				PauseCommands.Emplace(NewObject<UBBPauseCommandStub>(TestWorld, UBBPauseCommandStub::StaticClass()));
				PauseCommands.Emplace(NewObject<UBBPauseCommandStub>(TestWorld, UBBPauseCommandStub::StaticClass()));
				PauseCommands.Emplace(NewObject<UBBPauseCommandStub>(TestWorld, UBBPauseCommandStub::StaticClass()));
				PauseCommands.Emplace(NewObject<UBBPauseCommandStub>(TestWorld, UBBPauseCommandStub::StaticClass()));
				PauseCommands.Emplace(NewObject<UBBPauseCommandStub>(TestWorld, UBBPauseCommandStub::StaticClass()));

				for (UBBPauseCommandStub * & PauseCommand : PauseCommands)
				{
					Command->Add(PauseCommand);
				}

				for (int Executions = 1; Executions < 6; Executions++)
				{
					Command->Execute();

					for (UBBPauseCommandStub * & PauseCommand : PauseCommands)
					{
						TEST_TRUE(PauseCommand->GetNumExecutions() == Executions)
					}
				}

				return true;
			});
		});
	}
}