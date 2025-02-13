// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Data/BBBuildDataStub.h"
#include "Abilities/Tasks/BBAbilityTask.h"
#include "Abilities/Tasks/BBBuildTask.h"
#include "Actors/Components/BBWorkComponentStub.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "Jobs/Managers/BBJobManager.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(UBBBuildManagerSpec, "SaltLakeCity.Jobs.Managers.JobManager", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	TArray<UClass *> ManagerClasses;

	// SUT
	UPROPERTY()
	UBBJobManager * Manager = nullptr;

END_DEFINE_SPEC(UBBBuildManagerSpec)

void UBBBuildManagerSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBJobManager>(FString(TEXT("/Game/Jobs/Managers")), ManagerClasses);
	
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
		Manager = nullptr;

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & ManagerClass : ManagerClasses)
	{
		Describe("[" + ManagerClass->GetName() + "]", [this, ManagerClass]()
		{
			It("Given a new task and available consumers, expect the manager to reassign its tasks", [this, ManagerClass]()
			{
				Manager = NewObject<UBBJobManager>(TestWorld, ManagerClass);

				UTEST_TRUE("Manager is valid", IsValid(Manager))

				Manager->Initialize();

				TArray<UBBWorkComponentStub *> Consumers;
				Consumers.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));
				Consumers.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));
				Consumers.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));
				Consumers.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));
				Consumers.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));
				
				TArray<UBBBuildDataStub *> Builds;
				Builds.Emplace(NewObject<UBBBuildDataStub>(Manager, UBBBuildDataStub::StaticClass()));
				Builds.Emplace(NewObject<UBBBuildDataStub>(Manager, UBBBuildDataStub::StaticClass()));
				Builds.Emplace(NewObject<UBBBuildDataStub>(Manager, UBBBuildDataStub::StaticClass()));
				Builds.Emplace(NewObject<UBBBuildDataStub>(Manager, UBBBuildDataStub::StaticClass()));
				Builds.Emplace(NewObject<UBBBuildDataStub>(Manager, UBBBuildDataStub::StaticClass()));
				
				for (UBBWorkComponentStub * & Consumer : Consumers)
				{
					UTEST_TRUE("Consumer is valid", IsValid(Consumer))

					Manager->AddConsumer(Consumer);
				}

				int BuildTasks = 0;

				for (UBBBuildDataStub * & Build : Builds)
				{
					UTEST_TRUE("Build is valid", IsValid(Build))

					Manager->AddTask(Build);

					BuildTasks++;

					UTEST_TRUE("Manager has the correct number of tasks", Manager->GetTasksNum() == BuildTasks)

					TMap<UIBBAbilityTask *, int> ConsumersByTask;

					for (UBBWorkComponentStub * & Consumer : Consumers)
					{
						UIBBAbilityTask * ConsumerTask = Consumer->GetTask();

						if (IsValid(ConsumerTask))
						{
							ConsumersByTask.FindOrAdd(ConsumerTask)++;
						}
					}

					TEST_TRUE(ConsumersByTask.Num() == BuildTasks)

					for (TPair<UIBBAbilityTask *, int> TaskConsumersPair : ConsumersByTask)
					{
						TEST_TRUE(TaskConsumersPair.Value > 0)
					}
				}

				Manager->Finalize();

				return true;
			});

			It("Given a new task and no available consumers, expect the manager to queue it", [this, ManagerClass]()
			{
				Manager = NewObject<UBBJobManager>(TestWorld, ManagerClass);

				UTEST_TRUE("Manager is valid", IsValid(Manager))

				Manager->Initialize();

				TArray<UBBBuildDataStub *> Builds;
				Builds.Emplace(NewObject<UBBBuildDataStub>(Manager, UBBBuildDataStub::StaticClass()));
				Builds.Emplace(NewObject<UBBBuildDataStub>(Manager, UBBBuildDataStub::StaticClass()));
				Builds.Emplace(NewObject<UBBBuildDataStub>(Manager, UBBBuildDataStub::StaticClass()));
				Builds.Emplace(NewObject<UBBBuildDataStub>(Manager, UBBBuildDataStub::StaticClass()));
				Builds.Emplace(NewObject<UBBBuildDataStub>(Manager, UBBBuildDataStub::StaticClass()));

				TEST_TRUE(Manager->GetTasksNum() == 0)

				for (int Tasks = 1; Tasks < Builds.Num() + 1; Tasks++)
				{
					UBBBuildDataStub * Build = Builds[Tasks - 1];

					UTEST_TRUE("Build is valid", IsValid(Build))

					Manager->AddTask(Build);

					TEST_TRUE(Manager->GetTasksNum() == Tasks)
				}

				Manager->Finalize();

				return true;
			});

			It("Given a new consumer to be added, expect the manager to add it to its consumers", [this, ManagerClass]()
			{
				Manager = NewObject<UBBJobManager>(TestWorld, ManagerClass);

				UTEST_TRUE("Manager is valid", IsValid(Manager))

				Manager->Initialize();

				TArray<UBBWorkComponentStub *> Consumers;
				Consumers.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));
				Consumers.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));
				Consumers.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));
				Consumers.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));
				Consumers.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));

				TEST_TRUE(Manager->GetConsumersNum() == 0)

				for (int AddedConsumers = 1; AddedConsumers < Consumers.Num() + 1; AddedConsumers++)
				{
					UBBWorkComponentStub * Consumer = Consumers[AddedConsumers - 1];

					UTEST_TRUE("Consumer is valid", IsValid(Consumer))

					Manager->AddConsumer(Consumer);

					TEST_TRUE(Manager->GetConsumersNum() == AddedConsumers)
				}

				Manager->Finalize();

				return true;
			});

			It("Given a new consumer to be removed, expect the manager to remove it from its consumers", [this, ManagerClass]()
			{
				Manager = NewObject<UBBJobManager>(TestWorld, ManagerClass);

				UTEST_TRUE("Manager is valid", IsValid(Manager))

				Manager->Initialize();

				TArray<UBBWorkComponentStub *> Consumers;
				Consumers.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));
				Consumers.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));
				Consumers.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));
				Consumers.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));
				Consumers.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));

				for (UBBWorkComponentStub * & Consumer : Consumers)
				{
					UTEST_TRUE("Consumer is valid", IsValid(Consumer))

					Manager->AddConsumer(Consumer);
				}

				TEST_TRUE(Manager->GetConsumersNum() == Consumers.Num())

				for (int AddedConsumers = Consumers.Num() - 1; AddedConsumers >= 0; AddedConsumers--)
				{
					UBBWorkComponentStub * Consumer = Consumers[AddedConsumers];

					Manager->RemoveConsumer(Consumer);

					TEST_TRUE(Manager->GetConsumersNum() == AddedConsumers)
				}

				Manager->Finalize();

				return true;
			});

			It("Given a new assigned consumer to be removed and available consumers, expect the manager to reassign the consumers's task", [this, ManagerClass]()
			{
				Manager = NewObject<UBBJobManager>(TestWorld, ManagerClass);

				UTEST_TRUE("Manager is valid", IsValid(Manager))

				Manager->Initialize();

				TArray<UBBWorkComponentStub *> Consumers;
				Consumers.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));
				Consumers.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));
				Consumers.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));
				Consumers.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));
				Consumers.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));
				Consumers.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));
				Consumers.Emplace(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass()));

				for (UBBWorkComponentStub * & Consumer : Consumers)
				{
					UTEST_TRUE("Consumer is valid", IsValid(Consumer))

					Manager->AddConsumer(Consumer);
				}

				TArray<UBBWorkComponentStub *> AssignedConsumers;
				AssignedConsumers.Append(Consumers);

				TArray<UBBBuildDataStub *> Builds;
				Builds.Emplace(NewObject<UBBBuildDataStub>(Manager, UBBBuildDataStub::StaticClass()));
				Builds.Emplace(NewObject<UBBBuildDataStub>(Manager, UBBBuildDataStub::StaticClass()));
				Builds.Emplace(NewObject<UBBBuildDataStub>(Manager, UBBBuildDataStub::StaticClass()));
				Builds.Emplace(NewObject<UBBBuildDataStub>(Manager, UBBBuildDataStub::StaticClass()));
				Builds.Emplace(NewObject<UBBBuildDataStub>(Manager, UBBBuildDataStub::StaticClass()));
				Builds.Emplace(NewObject<UBBBuildDataStub>(Manager, UBBBuildDataStub::StaticClass()));

				int BuildTasks = 0;

				for (UBBBuildDataStub * & Build : Builds)
				{
					UTEST_TRUE("Build is valid", IsValid(Build))

					Manager->AddTask(Build);

					BuildTasks++;

					UTEST_TRUE("Manager has the correct number of tasks", Manager->GetTasksNum() == BuildTasks)
				}

				TMap<UIBBAbilityTask *, TArray<UBBWorkComponentStub *>> ConsumersByTask;
				TArray<TArray<UBBWorkComponentStub *>> TaskConsumers;

				while (Manager->GetConsumersNum() > 0)
				{
					ConsumersByTask.Empty();
					TaskConsumers.Empty();

					for (UBBWorkComponentStub * & AssignedConsumer : AssignedConsumers)
					{
						ConsumersByTask.FindOrAdd(AssignedConsumer->GetTask()).Emplace(AssignedConsumer);
					}

					ConsumersByTask.GenerateValueArray(TaskConsumers);
					
					for (int Index = 0; Index < TaskConsumers.Num(); Index++)
					{
						if (TaskConsumers[Index].Num() == 1)
						{
							UBBWorkComponentStub * RemovedConsumer = TaskConsumers[Index][0];

							Manager->RemoveConsumer(RemovedConsumer);

							AssignedConsumers.Remove(RemovedConsumer);

							Index = TaskConsumers.Num();
						}
					}

					ConsumersByTask.Empty();
					TaskConsumers.Empty();

					for (UBBWorkComponentStub * & AssignedConsumer : AssignedConsumers)
					{
						ConsumersByTask.FindOrAdd(AssignedConsumer->GetTask()).Emplace(AssignedConsumer);
					}

					ConsumersByTask.GenerateValueArray(TaskConsumers);

					if (Builds.Num() > 1)
					{
						for (TArray<UBBWorkComponentStub *> & CurrentTaskConsumers : TaskConsumers)
						{
							TEST_TRUE(CurrentTaskConsumers.Num() == 1)
						}

						TEST_TRUE(TaskConsumers.Num() == AssignedConsumers.Num())

						UBBBuildDataStub * RemovedBuild = Builds.Pop();

						Manager->RemoveTask(RemovedBuild);

						UTEST_TRUE("Manager has the correct number of tasks", Manager->GetTasksNum() == Builds.Num())
					}
					else
					{
						for (UBBWorkComponentStub * AssignedConsumer : AssignedConsumers)
						{
							Manager->RemoveConsumer(AssignedConsumer);
						}
					}
				}

				Manager->Finalize();

				return true;
			});
		});
	}
}