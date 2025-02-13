// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Data/BBBuildDataStub.h"
#include "Abilities/Tasks/BBBuildTask.h"
#include "Actors/Buildings/BBBuildingStub.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBBuildTaskSpec, "SaltLakeCity.Abilities.Tasks.BuildTask", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	TArray<UClass *> TaskClasses;

	int CompletedTasks = 0;

	// SUT
	UPROPERTY()
	UBBBuildTask * BuildTask = nullptr;

	void CompleteTask(UIBBAbilityTask * CompletedTask);

END_DEFINE_SPEC(UBBBuildTaskSpec)

void UBBBuildTaskSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBBuildTask>(FString(TEXT("/Game/Abilities/Tasks")), TaskClasses);

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
		BuildTask = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (auto & TaskClass : TaskClasses)
	{
		Describe("[" + TaskClass->GetName() + "]", [this, TaskClass]()
		{
			It("Given a new job type request, expect the build task to return its job type", [this, TaskClass]()
			{
				BuildTask = NewObject<UBBBuildTask>(TestWorld, TaskClass);

				UTEST_TRUE("Build Task is valid.", IsValid(BuildTask))

				TEST_TRUE(BuildTask->GetJobType() == EBBJob::Builder)

				return true;
			});

			It("Given a new event tag request, expect the build task to return its event tag", [this, TaskClass]()
			{
				BuildTask = NewObject<UBBBuildTask>(TestWorld, TaskClass);

				UTEST_TRUE("Build Task is valid.", IsValid(BuildTask))

				TEST_TRUE(BuildTask->GetEventTag() == FGameplayTag::RequestGameplayTag("Ability.AI.Build"))

				return true;
			});

			It("Given a new event data request, expect the build task to return its initialized event data", [this, TaskClass]()
			{
				BuildTask = NewObject<UBBBuildTask>(TestWorld, TaskClass);

				UTEST_TRUE("Build Task is valid.", IsValid(BuildTask))

				FGameplayEventData * EventData = BuildTask->GetEventData();

				UTEST_TRUE("Event Data is not null.", EventData != nullptr)

				TEST_TRUE(EventData->EventTag == FGameplayTag::RequestGameplayTag("Ability.AI.Build"))
				TEST_TRUE(EventData->OptionalObject == BuildTask)

				return true;
			});

			It("Given a new ability tags request, expect the build task to return its initialized ability tags", [this, TaskClass]()
			{
				BuildTask = NewObject<UBBBuildTask>(TestWorld, TaskClass);

				UTEST_TRUE("Build Task is valid.", IsValid(BuildTask))

				FGameplayTagContainer AbilityTags;
				AbilityTags.AddTag(FGameplayTag::RequestGameplayTag("Job.Builder"));

				TEST_TRUE(BuildTask->GetAbilityTags() == AbilityTags)

				return true;
			});

			It("Given a new progress, expect the build task to set its progress", [this, TaskClass]()
			{
				BuildTask = NewObject<UBBBuildTask>(TestWorld, TaskClass);

				UTEST_TRUE("Build Task is valid.", IsValid(BuildTask))

				TArray<float> Progresses;
				Progresses.Emplace(0.23f);
				Progresses.Emplace(0.67f);
				Progresses.Emplace(0.81f);
				Progresses.Emplace(0.54f);
				Progresses.Emplace(1.00f);

				for (auto & Progress : Progresses)
				{
					BuildTask->SetProgress(Progress);

					TEST_TRUE(BuildTask->GetProgress() == Progress)
				}

				return true;
			});

			It("Given a completed progress, expect the build task to broadcast the relative event", [this, TaskClass]()
			{
				BuildTask = NewObject<UBBBuildTask>(TestWorld, TaskClass);

				UTEST_TRUE("Build Task is valid.", IsValid(BuildTask))

				CompletedTasks = 0;

				FDelegateHandle Handle = BuildTask->OnTaskCompleted().AddRaw(this, &UBBBuildTaskSpec::CompleteTask);

				for (int Completions = 1; Completions < 6; Completions++)
				{
					BuildTask->SetProgress(1.0f);

					TEST_TRUE(CompletedTasks == Completions)
				}

				BuildTask->OnTaskCompleted().Remove(Handle);

				CompletedTasks = 0;

				return true;
			});

			It("Given a new build data, expect the build task to return its price upon request", [this, TaskClass]()
			{
				UBBBuildDataStub * BuildDataStub = NewObject<UBBBuildDataStub>(TestWorld, UBBBuildDataStub::StaticClass());

				UTEST_TRUE("Build Data stub is valid.", IsValid(BuildDataStub))

				BuildTask = NewObject<UBBBuildTask>(TestWorld, TaskClass);

				UTEST_TRUE("Build Task is valid.", IsValid(BuildTask))

				BuildTask->Decorate(BuildDataStub);

				TArray<float> Prices;
				Prices.Emplace(123.85f);
				Prices.Emplace(741.39f);
				Prices.Emplace(-467.53f);
				Prices.Emplace(-365.15f);
				Prices.Emplace(731.36f);

				for (auto & Price : Prices)
				{
					BuildDataStub->SetPrice(Price);

					TEST_TRUE(BuildTask->GetPrice() == Price)
				}

				return true;
			});

			It("Given a new build data, expect the build task to return its time upon request", [this, TaskClass]()
			{
				UBBBuildDataStub * BuildDataStub = NewObject<UBBBuildDataStub>(TestWorld, UBBBuildDataStub::StaticClass());

				UTEST_TRUE("Build Data stub is valid.", IsValid(BuildDataStub))

				BuildTask = NewObject<UBBBuildTask>(TestWorld, TaskClass);

				UTEST_TRUE("Build Task is valid.", IsValid(BuildTask))

				BuildTask->Decorate(BuildDataStub);

				TArray<float> Times;
				Times.Emplace(752.61f);
				Times.Emplace(-437.26f);
				Times.Emplace(678.41f);
				Times.Emplace(-731.71f);
				Times.Emplace(162.53f);

				for (auto & Time : Times)
				{
					BuildDataStub->SetTime(Time);

					TEST_TRUE(BuildTask->GetTime() == Time)
				}

				return true;
			});

			It("Given a new build data, expect the build task to return its buildables number upon request", [this, TaskClass]()
			{
				UBBBuildDataStub * BuildDataStub = NewObject<UBBBuildDataStub>(TestWorld, UBBBuildDataStub::StaticClass());

				UTEST_TRUE("Build Data stub is valid.", IsValid(BuildDataStub))

				BuildTask = NewObject<UBBBuildTask>(TestWorld, TaskClass);

				UTEST_TRUE("Build Task is valid.", IsValid(BuildTask))

				BuildTask->Decorate(BuildDataStub);

				FActorSpawnParameters SpawnParameters;
				SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				TArray<TArray<TScriptInterface<IBBBuildable>>> AllBuildables;
				TArray<TScriptInterface<IBBBuildable>> NewBuildables;

				NewBuildables.Emplace(TScriptInterface<IBBBuildable>(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters)));
				NewBuildables.Emplace(TScriptInterface<IBBBuildable>(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters)));
				
				AllBuildables.Emplace(NewBuildables);
				NewBuildables.Empty();

				NewBuildables.Emplace(TScriptInterface<IBBBuildable>(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters)));
				
				AllBuildables.Emplace(NewBuildables);
				NewBuildables.Empty();

				NewBuildables.Emplace(TScriptInterface<IBBBuildable>(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters)));
				NewBuildables.Emplace(TScriptInterface<IBBBuildable>(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters)));
				
				AllBuildables.Emplace(NewBuildables);
				NewBuildables.Empty();

				NewBuildables.Emplace(TScriptInterface<IBBBuildable>(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters)));
				NewBuildables.Emplace(TScriptInterface<IBBBuildable>(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters)));
				NewBuildables.Emplace(TScriptInterface<IBBBuildable>(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters)));

				AllBuildables.Emplace(NewBuildables);
				NewBuildables.Empty();

				NewBuildables.Emplace(TScriptInterface<IBBBuildable>(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters)));
				NewBuildables.Emplace(TScriptInterface<IBBBuildable>(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters)));
				
				AllBuildables.Emplace(NewBuildables);
				NewBuildables.Empty();

				for (auto & Buildables : AllBuildables)
				{
					BuildDataStub->SetBuildables(Buildables);

					TEST_TRUE(BuildTask->GetNumBuildables() == Buildables.Num())
				}

				for (auto & Buildables : AllBuildables)
				{
					for (auto & Buildable : Buildables)
					{
						TestWorld->DestroyActor(Buildable->ToActor());
					}
				}

				return true;
			});

			It("Given a new build data, expect the build task to return its buildables upon request", [this, TaskClass]()
			{
				UBBBuildDataStub * BuildDataStub = NewObject<UBBBuildDataStub>(TestWorld, UBBBuildDataStub::StaticClass());

				UTEST_TRUE("Build Data stub is valid.", IsValid(BuildDataStub))

				BuildTask = NewObject<UBBBuildTask>(TestWorld, TaskClass);

				UTEST_TRUE("Build Task is valid.", IsValid(BuildTask))

				BuildTask->Decorate(BuildDataStub);

				FActorSpawnParameters SpawnParameters;
				SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				TArray<TArray<TScriptInterface<IBBBuildable>>> AllBuildables;
				TArray<TScriptInterface<IBBBuildable>> NewBuildables;

				NewBuildables.Emplace(TScriptInterface<IBBBuildable>(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters)));
				
				AllBuildables.Emplace(NewBuildables);
				NewBuildables.Empty();

				NewBuildables.Emplace(TScriptInterface<IBBBuildable>(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters)));
				NewBuildables.Emplace(TScriptInterface<IBBBuildable>(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters)));

				AllBuildables.Emplace(NewBuildables);
				NewBuildables.Empty();

				NewBuildables.Emplace(TScriptInterface<IBBBuildable>(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters)));
				NewBuildables.Emplace(TScriptInterface<IBBBuildable>(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters)));
				NewBuildables.Emplace(TScriptInterface<IBBBuildable>(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters)));

				AllBuildables.Emplace(NewBuildables);
				NewBuildables.Empty();

				NewBuildables.Emplace(TScriptInterface<IBBBuildable>(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters)));
				
				AllBuildables.Emplace(NewBuildables);
				NewBuildables.Empty();

				NewBuildables.Emplace(TScriptInterface<IBBBuildable>(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters)));
				NewBuildables.Emplace(TScriptInterface<IBBBuildable>(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters)));
				NewBuildables.Emplace(TScriptInterface<IBBBuildable>(TestWorld->SpawnActor<ABBBuildingStub>(ABBBuildingStub::StaticClass(), SpawnParameters)));

				AllBuildables.Emplace(NewBuildables);
				NewBuildables.Empty();

				for (auto & Buildables : AllBuildables)
				{
					BuildDataStub->SetBuildables(Buildables);

					for (int Index = 0; Index < Buildables.Num(); Index++)
					{
						TEST_TRUE(BuildTask->GetBuildable(Index) == Buildables[Index])
					}
				}

				for (auto & Buildables : AllBuildables)
				{
					for (auto & Buildable : Buildables)
					{
						TestWorld->DestroyActor(Buildable->ToActor());
					}
				}

				return true;
			});
		});
	}
}

void UBBBuildTaskSpec::CompleteTask(UIBBAbilityTask * CompletedTask)
{
	CompletedTasks++;
}