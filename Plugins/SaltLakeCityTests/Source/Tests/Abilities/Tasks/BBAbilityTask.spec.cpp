// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/BBAbilityTask.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBAbilityTaskSpec,
	"SaltLakeCity.Abilities.Tasks.AbilityTask",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	TArray<UClass *> TaskClasses;

	// SUT
	UPROPERTY()
	UBBAbilityTask * AbilityTask = nullptr;

END_DEFINE_SPEC(UBBAbilityTaskSpec)

void UBBAbilityTaskSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBAbilityTask>(FString(TEXT("/Game/Abilities/Task")), TaskClasses);

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
		AbilityTask = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (auto & TaskClass : TaskClasses)
	{
		Describe("[" + TaskClass->GetName() + "]", [this, TaskClass]()
		{
			It("Given a , expect the ability task to ", [this, TaskClass]()
			{
			});
		});
	}
}