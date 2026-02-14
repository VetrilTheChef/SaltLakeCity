// SaltLakeCity 5.7

#include "BBJobManager.h"
#include "Abilities/Data/Interfaces/IBBAbilityData.h"
#include "Abilities/Tasks/Interfaces/IBBAbilityTask.h"
#include "Actors/Components/Interfaces/IBBWorkComponent.h"
#include "Jobs/Queues/Interfaces/IBBConsumerQueue.h"
#include "Jobs/Queues/Interfaces/IBBTaskQueue.h"

UBBJobManager::UBBJobManager() :
	Super()
{
	Job = EBBJob::None;

	TaskQueue = nullptr;
	ConsumerQueue = nullptr;
}

void UBBJobManager::Initialize()
{
	CreateQueues();
}

void UBBJobManager::Finalize()
{
	DestroyQueues();
}

void UBBJobManager::AddTask(const UIBBAbilityData * AbilityData)
{
	verifyf(!TaskClass.IsNull(), TEXT("Task class is null."));

	UIBBAbilityTask * Task = NewObject<UIBBAbilityTask>(this, TaskClass.LoadSynchronous());

	verifyf(IsValid(Task), TEXT("Task is invalid."));

	Task->Decorate(AbilityData);

	Task->OnTaskCompleted().AddUObject(this, & UBBJobManager::CompleteTask);

	FBBManagedTask ManagedTask(Task);

	verifyf(IsValid(TaskQueue), TEXT("Task Queue is invalid."));

	TaskQueue->Add(ManagedTask);

	Manage();
}

void UBBJobManager::RemoveTask(const UIBBAbilityData * AbilityData)
{
	verifyf(IsValid(TaskQueue), TEXT("Task Queue is invalid."));

	UIBBTaskQueueIterator * TaskIterator = TaskQueue->GetIterator();

	verifyf(IsValid(TaskIterator), TEXT("Task Iterator is invalid"));

	FBBManagedTask ManagedTask;

	while (TaskIterator->HasNext())
	{
		TaskIterator->Next(ManagedTask);

		UIBBAbilityTask * AbilityTask = ManagedTask.AbilityTask;

		verifyf(IsValid(AbilityTask), TEXT("Ability Task is invalid."));

		if (AbilityTask->GetAbilityData() == AbilityData)
		{
			AbilityTask->OnTaskCompleted().RemoveAll(this);

			TaskQueue->Remove(ManagedTask);

			break;
		}
	}

	Manage();
}

int UBBJobManager::GetTasksNum()
{
	verifyf(IsValid(TaskQueue), TEXT("Task Queue is invalid."));

	return TaskQueue->GetTasksNum();
}

void UBBJobManager::AddConsumer(UIBBWorkComponent * Consumer)
{
	verifyf(IsValid(Consumer), TEXT("Consumer is invalid."));

	//Consumer->OnTaskCompleted().AddUObject(this, & UBBJobManager::CompleteTask);

	FBBManagedConsumer ManagedConsumer = FBBManagedConsumer();

	verifyf(!FindManagedConsumer(ManagedConsumer, Consumer), TEXT("Consumer was already added."));

	ManagedConsumer.Consumer = Consumer;

	ConsumerQueue->Add(ManagedConsumer);

	Manage();
}

void UBBJobManager::RemoveConsumer(UIBBWorkComponent * Consumer)
{
	verifyf(IsValid(Consumer), TEXT("Consumer is invalid."));
	
	//Consumer->OnTaskCompleted().RemoveAll(this);

	FBBManagedConsumer ManagedConsumer;

	if (FindManagedConsumer(ManagedConsumer, Consumer))
	{
		ConsumerQueue->Remove(ManagedConsumer);
	}

	Manage();
}

int UBBJobManager::GetConsumersNum()
{
	verifyf(IsValid(ConsumerQueue), TEXT("Consumer Queue is invalid."));

	return ConsumerQueue->GetConsumersNum();
}

void UBBJobManager::CompleteTask(UIBBAbilityTask * AbilityTask)
{
	verifyf(IsValid(AbilityTask), TEXT("Completed Task is invalid."));
	verifyf(AbilityTask->GetProgress() >= 1.0f, TEXT("Completed Task's progress is less than 100%%."));

	FBBManagedTask ManagedTask;
	TArray<FBBManagedConsumer> ManagedConsumers(ManagedTask.Consumers);

	verifyf(FindManagedTask(ManagedTask, AbilityTask), TEXT("Could not find Managed Task."));

	for (FBBManagedConsumer & ManagedConsumer : ManagedConsumers)
	{
		verifyf(IsValid(ManagedConsumer.Consumer), TEXT("Consumer is invalid."));

		verifyf(UnassignTask(ManagedConsumer, ManagedTask), TEXT("Error unassigning completed Task from Consumer."));
		verifyf(UnassignConsumer(ManagedConsumer, ManagedTask), TEXT("Error unassigning Consumer from completed Task"));
	}

	Manage();
}



void UBBJobManager::CreateQueues()
{
	DestroyQueues();

	CreateTaskQueue();
	CreateConsumerQueue();
}

void UBBJobManager::CreateTaskQueue()
{
	verifyf(!TaskQueueClass.IsNull(), TEXT("Task Queue class is null."));

	TaskQueue = NewObject<UIBBTaskQueue>(this, TaskQueueClass.LoadSynchronous());
}

void UBBJobManager::CreateConsumerQueue()
{
	verifyf(!ConsumerQueueClass.IsNull(), TEXT("Consumer Queue class is null."));

	ConsumerQueue = NewObject<UIBBConsumerQueue>(this, ConsumerQueueClass.LoadSynchronous());

	verifyf(IsValid(ConsumerQueue), TEXT("Consumer Queue is invalid."));

	ConsumerQueue->Initialize(Job);
}

void UBBJobManager::DestroyQueues()
{
	DestroyTaskQueue();
	DestroyConsumerQueue();
}

void UBBJobManager::DestroyTaskQueue()
{
	if (IsValid(TaskQueue))
	{
		TaskQueue->MarkAsGarbage();
	}

	TaskQueue = nullptr;
}

void UBBJobManager::DestroyConsumerQueue()
{
	if (IsValid(ConsumerQueue))
	{
		ConsumerQueue->Finalize();

		ConsumerQueue->MarkAsGarbage();
	}

	ConsumerQueue = nullptr;
}

void UBBJobManager::SubscribeToQueues()
{
}

void UBBJobManager::UnsubscribeFromQueues()
{
}

void UBBJobManager::Manage()
{
	verifyf(IsValid(TaskQueue), TEXT("Task Queue is invalid"));
	verifyf(IsValid(ConsumerQueue), TEXT("Consumer Queue is invalid"));

	if (ConsumerQueue->GetConsumersNum() && TaskQueue->GetTasksNum())
	{
		UIBBConsumerQueueIterator * ConsumerIterator = ConsumerQueue->GetIterator();
		UIBBTaskQueueIterator * TaskIterator = TaskQueue->GetIterator();

		verifyf(IsValid(ConsumerIterator), TEXT("Consumer Iterator is invalid"));
		verifyf(IsValid(TaskIterator), TEXT("Task Iterator is invalid"));

		while (ConsumerIterator->HasNext())
		{
			FBBManagedConsumer ManagedConsumer;

			ConsumerIterator->Next(ManagedConsumer);

			FBBManagedTask OldManagedTask;

			if (TaskQueue->GetAssignedTask(ManagedConsumer, OldManagedTask))
			{
				UnassignTask(ManagedConsumer, OldManagedTask);
				UnassignConsumer(ManagedConsumer, OldManagedTask);
			}

			if (TaskIterator->HasNext())
			{
				FBBManagedTask NewManagedTask;
				TaskIterator->Next(NewManagedTask);

				AssignConsumer(ManagedConsumer, NewManagedTask);
				AssignTask(ManagedConsumer, NewManagedTask);
			}
		}
	}
}

bool UBBJobManager::FindManagedTask(FBBManagedTask & ManagedTask, const UIBBAbilityTask * Task) const
{
	verifyf(IsValid(TaskQueue), TEXT("Task Queue is invalid"));

	UIBBTaskQueueIterator * TaskIterator = TaskQueue->GetIterator();

	verifyf(IsValid(TaskIterator), TEXT("Task Queue Iterator is invalid."));

	while (TaskIterator->HasNext())
	{
		TaskIterator->Next(ManagedTask);

		if (ManagedTask.AbilityTask == Task)
		{
			return true;
		}
	}

	return false;
}

bool UBBJobManager::FindManagedConsumer(FBBManagedConsumer & ManagedConsumer, const UIBBWorkComponent * Consumer) const
{
	verifyf(IsValid(ConsumerQueue), TEXT("Consumer Queue is invalid."));

	UIBBConsumerQueueIterator * ConsumerIterator = ConsumerQueue->GetIterator();

	verifyf(IsValid(ConsumerIterator), TEXT("Consumer Queue Iterator is invalid."));

	while (ConsumerIterator->HasNext())
	{
		ConsumerIterator->Next(ManagedConsumer);

		if (ManagedConsumer.Consumer == Consumer)
		{
			return true;
		}
	}

	return false;
}

bool UBBJobManager::AssignTask(FBBManagedConsumer & ManagedConsumer, FBBManagedTask & ManagedTask)
{
	verifyf(IsValid(ManagedConsumer.Consumer), TEXT("Consumer is invalid."));

	ManagedConsumer.Consumer->AssignTask(ManagedTask.AbilityTask);
	ManagedConsumer.Consumer->StartTask();

	return ManagedConsumer.Consumer->IsWorking();
}

bool UBBJobManager::UnassignTask(FBBManagedConsumer & ManagedConsumer, FBBManagedTask & ManagedTask)
{
	verifyf(IsValid(ManagedConsumer.Consumer), TEXT("Consumer is invalid."));

	verifyf(ManagedTask.AbilityTask == ManagedConsumer.Consumer->GetTask(), TEXT("Assigned Task is not the Task that should be unassigned."));
		
	ManagedConsumer.Consumer->StopTask();
	ManagedConsumer.Consumer->AssignTask(nullptr);

	return IsValid(ManagedTask.AbilityTask);
}

bool UBBJobManager::AssignConsumer(FBBManagedConsumer & ManagedConsumer, FBBManagedTask & ManagedTask)
{
	return ManagedTask.Consumers.AddUnique(ManagedConsumer) >= 0;
}

bool UBBJobManager::UnassignConsumer(FBBManagedConsumer & ManagedConsumer, FBBManagedTask & ManagedTask)
{
	return ManagedTask.Consumers.Remove(ManagedConsumer) > 0;
}