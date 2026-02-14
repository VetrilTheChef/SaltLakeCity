// SaltLakeCity 4.27

#include "BBTaskQueue.h"
#include "Abilities/Tasks/Interfaces/IBBAbilityTask.h"

UBBTaskQueue::UBBTaskQueue() :
	Super()
{
	ManagedTasks.Heapify(UBBTaskQueue::SortTasks);
}

void UBBTaskQueue::Add(FBBManagedTask & ManagedTask)
{
	if (!ManagedTasks.ContainsByPredicate([& ManagedTask](FBBManagedTask & CurrentManagedTask)
		{
			return IsValid(ManagedTask.AbilityTask) && (CurrentManagedTask == ManagedTask);
		}))
	{
		ManagedTasks.HeapPush(ManagedTask, UBBTaskQueue::SortTasks);
		//ManagedTasks.HeapPush(Forward<FBBManagedTask>(ManagedTask), UBBTaskQueue::SortTasks);
	}
}

int UBBTaskQueue::Remove(FBBManagedTask & ManagedTask)
{
	int TasksNum = ManagedTasks.Num();

	for (int Index = TasksNum - 1; Index >= 0; Index--)
	{
		if (ManagedTasks[Index].AbilityTask == ManagedTask.AbilityTask)
		{
			ManagedTasks.RemoveAt(Index);
		}
	}

	return TasksNum - ManagedTasks.Num();
}

bool UBBTaskQueue::Get(FBBManagedTask & ManagedTask)
{
	ManagedTask = FBBManagedTask();

	if (this->HasTask())
	{
		Sort();

		ManagedTasks.HeapPop(Forward<FBBManagedTask &>(ManagedTask), UBBTaskQueue::SortTasks, EAllowShrinking::Yes);
	}

	return IsValid(ManagedTask.AbilityTask);
}

bool UBBTaskQueue::HasTask() const
{
	return (ManagedTasks.Num() > 0);
}

int UBBTaskQueue::GetTasksNum() const
{
	return ManagedTasks.Num();
}

bool UBBTaskQueue::GetAssignedTask(FBBManagedConsumer & ManagedConsumer, FBBManagedTask & ManagedTask) const
{
	for (const FBBManagedTask & CurrentManagedTask : ManagedTasks)
	{
		if (CurrentManagedTask.Consumers.Contains(ManagedConsumer))
		{
			ManagedTask = CurrentManagedTask;

			return true;
		}
	}

	return false;
}

UIBBTaskQueueIterator * UBBTaskQueue::GetIterator()
{
	UBBTaskQueueIterator * Iterator = NewObject<UBBTaskQueueIterator>(this, UBBTaskQueueIterator::StaticClass());

	verifyf(IsValid(Iterator), TEXT("Task Queue Iterator is invalid."));

	Iterator->Initialize(this, true);

	return Iterator;
}



void UBBTaskQueue::Sort()
{
	for (FBBManagedTask & ManagedTask : ManagedTasks)
	{
		verifyf(IsValid(ManagedTask.AbilityTask), TEXT("Task is invalid."));

		ManagedTask.QueueTime += 1;

		ManagedTask.Priority = PrioritizeByQueueTime(ManagedTask);
		ManagedTask.Priority += PrioritizeByProgress(ManagedTask);
		ManagedTask.Priority += PrioritizeByWorkers(ManagedTask);
	}

	ManagedTasks.HeapSort(UBBTaskQueue::SortTasks);
}

bool UBBTaskQueue::SortTasks(FBBManagedTask const & lhs, FBBManagedTask const & rhs)
{
	return lhs > rhs;
}

int UBBTaskQueue::PrioritizeByQueueTime(FBBManagedTask & ManagedTask) const
{
	return ManagedTask.QueueTime;
}

int UBBTaskQueue::PrioritizeByProgress(FBBManagedTask & ManagedTask) const
{
	UIBBAbilityTask * AbilityTask = ManagedTask.AbilityTask;

	verifyf(IsValid(AbilityTask), TEXT("Ability Task is invalid."));

	// Progress: [0.0f, 1.0f]
	return (int)(10.0f * AbilityTask->GetProgress());
}

int UBBTaskQueue::PrioritizeByWorkers(FBBManagedTask & ManagedTask) const
{
	int Consumers = ManagedTask.Consumers.Num();

	return (Consumers * -10);
}


UBBTaskQueueIterator::UBBTaskQueueIterator() :
	Super()
{
	TaskQueue = nullptr;

	Index = 0;
}

void UBBTaskQueueIterator::Initialize(UBBTaskQueue * NewTaskQueue, bool Loop)
{
	verifyf(IsValid(NewTaskQueue), TEXT("New Task Queue is invalid."));

	TaskQueue = NewTaskQueue;

	LoopTasks = Loop;
}

bool UBBTaskQueueIterator::HasNext()
{
	verifyf(IsValid(TaskQueue), TEXT("Task Queue is invalid."));

	return (LoopTasks || Index < TaskQueue->ManagedTasks.Num());
}

void UBBTaskQueueIterator::Next(FBBManagedTask & NextManagedTask)
{
	verifyf(IsValid(TaskQueue), TEXT("Task Queue is invalid."));

	if (LoopTasks)
	{
		Index = (Index < TaskQueue->ManagedTasks.Num()) ? Index : 0;
	}

	NextManagedTask = TaskQueue->ManagedTasks[Index++];
}