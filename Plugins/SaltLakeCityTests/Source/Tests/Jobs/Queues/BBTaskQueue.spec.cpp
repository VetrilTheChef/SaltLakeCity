// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/BBBuildTaskStub.h"
#include "Actors/Components/BBWorkComponentStub.h"
#include "Jobs/Queues/BBTaskQueue.h"
#include "GameInstances/BBGameInstanceStub.h"
#include "Tests/BBTestUtil.h"

BEGIN_DEFINE_SPEC(
	UBBTaskQueueSpec,
	"SaltLakeCity.Jobs.Queues.TaskQueue",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext
)

	UPROPERTY()
	UWorld * TestWorld = nullptr;

	UPROPERTY()
	UBBGameInstanceStub * GameInstance = nullptr;

	UPROPERTY()
	TArray<FBBManagedTask> ManagedTasks;

	UPROPERTY()
	TArray<UClass *> QueueClasses;

	// SUT
	UPROPERTY()
	UBBTaskQueue * Queue = nullptr;

END_DEFINE_SPEC(UBBTaskQueueSpec)

void UBBTaskQueueSpec::Define()
{
	UBBTestUtil::GetTestClasses<UBBTaskQueue>(FString(TEXT("/Game/Jobs/Queues")), QueueClasses);
	
	BeforeEach([this]()
	{
		TestWorld = UBBTestUtil::OpenTestWorld();

		UTEST_TRUE("Test World is valid", IsValid(TestWorld))

		GameInstance = TestWorld->GetGameInstance<UBBGameInstanceStub>();

		UTEST_TRUE("Game Instance is valid", IsValid(GameInstance))

		ManagedTasks.Empty();

		for (int Tasks = 0; Tasks < 5; Tasks++)
		{
			UBBBuildTaskStub * BuildTask = NewObject<UBBBuildTaskStub>(TestWorld, UBBBuildTaskStub::StaticClass());

			ManagedTasks.Emplace(FBBManagedTask(BuildTask));
		}

		return true;
	});

	AfterEach([this]()
	{
		Queue = nullptr;

		for (FBBManagedTask & ManagedTask : ManagedTasks)
		{
			ManagedTask.AbilityTask->MarkAsGarbage();
			ManagedTask.AbilityTask = nullptr;
		}

		ManagedTasks.Empty();

		GameInstance = nullptr;

		UBBTestUtil::CloseTestWorld(TestWorld);
	});

	for (UClass * & QueueClass : QueueClasses)
	{
		Describe("[" + QueueClass->GetName() + "]", [this, QueueClass]()
		{
			It("Given an added task, expect the queue to return the correct tasks number", [this, QueueClass]()
			{
				Queue = NewObject<UBBTaskQueue>(TestWorld, QueueClass);

				UTEST_TRUE("Queue is valid", IsValid(Queue))

				int TasksNum = 0;

				TEST_TRUE(Queue->GetTasksNum() == TasksNum)

				for (FBBManagedTask & ManagedTask : ManagedTasks)
				{
					Queue->Add(ManagedTask);
					TasksNum++;

					TEST_TRUE(Queue->GetTasksNum() == TasksNum)
				}

				return true;
			});

			It("Given a removed task, expect the queue to return the correct tasks number", [this, QueueClass]()
			{
				Queue = NewObject<UBBTaskQueue>(TestWorld, QueueClass);

				UTEST_TRUE("Queue is valid", IsValid(Queue))

				int TasksNum = ManagedTasks.Num();

				for (FBBManagedTask & ManagedTask : ManagedTasks)
				{
					Queue->Add(ManagedTask);
				}

				TEST_TRUE(Queue->GetTasksNum() == TasksNum)

				for (TasksNum = TasksNum - 1; TasksNum >= 0; TasksNum--)
				{
					Queue->Remove(ManagedTasks[TasksNum]);

					TEST_TRUE(Queue->GetTasksNum() == TasksNum)
				}

				return true;
			});

			It("Given a task presence request, expect the queue to return true if it has tasks", [this, QueueClass]()
			{
				Queue = NewObject<UBBTaskQueue>(TestWorld, QueueClass);

				UTEST_TRUE("Queue is valid", IsValid(Queue))

				TEST_TRUE(Queue->HasTask() == false)

				Queue->Add(ManagedTasks[0]);

				TEST_TRUE(Queue->HasTask() == true)

				Queue->Remove(ManagedTasks[0]);

				TEST_TRUE(Queue->HasTask() == false)

				Queue->Add(ManagedTasks[0]);

				TEST_TRUE(Queue->HasTask() == true)

				Queue->Add(ManagedTasks[1]);

				TEST_TRUE(Queue->HasTask() == true)

				Queue->Remove(ManagedTasks[0]);

				TEST_TRUE(Queue->HasTask() == true)

				Queue->Add(ManagedTasks[2]);

				TEST_TRUE(Queue->HasTask() == true)

				Queue->Remove(ManagedTasks[1]);

				TEST_TRUE(Queue->HasTask() == true)

				Queue->Remove(ManagedTasks[2]);

				TEST_TRUE(Queue->HasTask() == false)

				return true;
			});

			It("Given a managed worker, expect the queue to return its managed task", [this, QueueClass]()
			{
				Queue = NewObject<UBBTaskQueue>(TestWorld, QueueClass);

				UTEST_TRUE("Queue is valid", IsValid(Queue))

				TArray<FBBManagedConsumer> ManagedConsumers;
				ManagedConsumers.Emplace(FBBManagedConsumer(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass())));
				ManagedConsumers.Emplace(FBBManagedConsumer(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass())));
				ManagedConsumers.Emplace(FBBManagedConsumer(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass())));
				ManagedConsumers.Emplace(FBBManagedConsumer(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass())));
				ManagedConsumers.Emplace(FBBManagedConsumer(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass())));
				ManagedConsumers.Emplace(FBBManagedConsumer(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass())));
				ManagedConsumers.Emplace(FBBManagedConsumer(NewObject<UBBWorkComponentStub>(TestWorld, UBBWorkComponentStub::StaticClass())));

				ManagedTasks[3].Consumers.Emplace(ManagedConsumers[0]);
				ManagedTasks[2].Consumers.Emplace(ManagedConsumers[1]);
				ManagedTasks[4].Consumers.Emplace(ManagedConsumers[2]);
				ManagedTasks[1].Consumers.Emplace(ManagedConsumers[3]);
				ManagedTasks[0].Consumers.Emplace(ManagedConsumers[4]);
				ManagedTasks[2].Consumers.Emplace(ManagedConsumers[5]);
				ManagedTasks[4].Consumers.Emplace(ManagedConsumers[6]);

				for (FBBManagedTask & ManagedTask : ManagedTasks)
				{
					Queue->Add(ManagedTask);
				}

				UTEST_TRUE("Queue has the correct number of tasks", Queue->GetTasksNum() == ManagedTasks.Num())

				FBBManagedTask Task;

				UTEST_TRUE("Managed Task found", Queue->GetAssignedTask(ManagedConsumers[0], Task))
				TEST_TRUE(Task == ManagedTasks[3])

				UTEST_TRUE("Managed Task found", Queue->GetAssignedTask(ManagedConsumers[1], Task))
				TEST_TRUE(Task == ManagedTasks[2])

				UTEST_TRUE("Managed Task found", Queue->GetAssignedTask(ManagedConsumers[2], Task))
				TEST_TRUE(Task == ManagedTasks[4])

				UTEST_TRUE("Managed Task found", Queue->GetAssignedTask(ManagedConsumers[3], Task))
				TEST_TRUE(Task == ManagedTasks[1])

				UTEST_TRUE("Managed Task found", Queue->GetAssignedTask(ManagedConsumers[4], Task))
				TEST_TRUE(Task == ManagedTasks[0])

				UTEST_TRUE("Managed Task found", Queue->GetAssignedTask(ManagedConsumers[5], Task))
				TEST_TRUE(Task == ManagedTasks[2])

				UTEST_TRUE("Managed Task found", Queue->GetAssignedTask(ManagedConsumers[6], Task))
				TEST_TRUE(Task == ManagedTasks[4])

				return true;
			});

			It("Given a queue iterator request, expect the queue to return it", [this, QueueClass]()
			{
				Queue = NewObject<UBBTaskQueue>(TestWorld, QueueClass);

				UTEST_TRUE("Queue is valid", IsValid(Queue))

				for (FBBManagedTask & ManagedTask : ManagedTasks)
				{
					Queue->Add(ManagedTask);
				}

				UTEST_TRUE("Queue has the correct number of tasks", Queue->GetTasksNum() == ManagedTasks.Num())

				UIBBTaskQueueIterator * Iterator = Queue->GetIterator();

				UTEST_TRUE("Queue Iterator is valid", IsValid(Iterator))

				TArray<FBBManagedTask> RemainingTasks;
				RemainingTasks.Append(ManagedTasks);

				for (int Index = 0; Index < Queue->GetTasksNum(); Index++)
				{
					FBBManagedTask ManagedTask;

					UTEST_TRUE("Queue Iterator has next", Iterator->HasNext())

					Iterator->Next(ManagedTask);

					UTEST_TRUE("Task is one of the remaining tasks", RemainingTasks.Contains(ManagedTask))

					RemainingTasks.Remove(ManagedTask);
				}

				UTEST_TRUE("Queue Iterator has returned all tasks", RemainingTasks.Num() == 0)

				return true;
			});
		});
	}
}