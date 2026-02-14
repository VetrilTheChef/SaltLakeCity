// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Commands/Controllers/BBPauseCommand.h"
#include "Controllers/BBPlayerControllerStub.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBPauseCommandSpec,
	"SaltLakeCity.Commands.Controllers.PauseCommand",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	ABBPlayerControllerStub * Controller = nullptr;

	UPROPERTY()
	TArray<UClass *> CommandClasses;

	// SUT
	UPROPERTY()
	UBBPauseCommand * Command = nullptr;

	FActorSpawnParameters SpawnParameters;

END_DEFINE_SPEC(UBBPauseCommandSpec)

void UBBPauseCommandSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBPauseCommand>(FString(TEXT("/Game/Commands/Controllers")), CommandClasses);

	SpawnParameters = FActorSpawnParameters();
	SpawnParameters.bNoFail = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		Controller = TestWorld->SpawnActor<ABBPlayerControllerStub>(ABBPlayerControllerStub::StaticClass(), SpawnParameters);

		UTEST_TRUE("Controller is valid", IsValid(Controller))

		return true;
	});

	AfterEach([this]()
	{
		Command = nullptr;

		TestWorld->DestroyActor(Controller);

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & CommandClass : CommandClasses)
	{
		Describe("[" + CommandClass->GetName() + "]", [this, CommandClass]()
		{
			It("Given a new starting pause state, expect the command to toggle it upon execution", [this, CommandClass]()
			{
				Command = NewObject<UBBPauseCommand>(TestWorld, CommandClass);

				UTEST_TRUE("Command is valid", IsValid(Command))

				Command->SetController(Controller);

				bool Paused = Controller->IsPaused();

				for (int Execution = 0; Execution < 5; Execution++)
				{
					Command->Execute();

					TEST_TRUE(Controller->IsPaused() == !Paused)

					Paused = Controller->IsPaused();
				}

				return true;
			});
		});
	}
}