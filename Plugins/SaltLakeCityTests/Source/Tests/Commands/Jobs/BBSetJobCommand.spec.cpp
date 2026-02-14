// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Actors/Components/BBWorkComponentStub.h"
#include "Commands/Jobs/BBSetJobCommand.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBSetJobCommandSpec,
	"SaltLakeCity.Commands.Jobs.SetJobCommand",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	UBBWorkComponentStub * WorkComponent = nullptr;

	UPROPERTY()
	TArray<UClass *> CommandClasses;

	// SUT
	UPROPERTY()
	UBBSetJobCommand * Command = nullptr;

END_DEFINE_SPEC(UBBSetJobCommandSpec)

void UBBSetJobCommandSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBSetJobCommand>(FString(TEXT("/Game/Commands/Jobs")), CommandClasses);

	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		WorkComponent = NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass());

		UTEST_TRUE("Work Component is valid", IsValid(WorkComponent))

		return true;
	});

	AfterEach([this]()
	{
		Command = nullptr;

		WorkComponent = nullptr;

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & CommandClass : CommandClasses)
	{
		Describe("[" + CommandClass->GetName() + "]", [this, CommandClass]()
		{
			It("Given a new work component, expect the command to set its job upon execution", [this, CommandClass]()
			{
				Command = NewObject<UBBSetJobCommand>(TestWorld, CommandClass);

				UTEST_TRUE("Command is valid", IsValid(Command))

				TArray<EBBJob> Jobs;
				Jobs.Empty();
				Jobs.Emplace(EBBJob::Builder);
				Jobs.Emplace(EBBJob::Idle);
				Jobs.Emplace(EBBJob::Builder);
				Jobs.Emplace(EBBJob::None);
				Jobs.Emplace(EBBJob::Idle);

				Command->SetWorkComponent(WorkComponent);

				for (EBBJob & Job : Jobs)
				{
					Command->SetJob(Job);

					Command->Execute();

					TEST_TRUE(WorkComponent->GetJob() == Job)
				}

				return true;
			});
		});
	}
}