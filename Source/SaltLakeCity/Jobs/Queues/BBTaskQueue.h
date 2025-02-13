// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Jobs/Includes/BBManagedTaskStruct.h"
#include "Jobs/Queues/Interfaces/IBBTaskQueue.h"
#include "BBTaskQueue.generated.h"

/**
 *
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBTaskQueue : public UIBBTaskQueue
{
	GENERATED_BODY()

	public:
		UBBTaskQueue();

		virtual void Add(FBBManagedTask & ManagedTask) override;

		virtual int Remove(FBBManagedTask & ManagedTask) override;

		virtual bool Get(FBBManagedTask & ManagedTask) override;

		virtual bool HasTask() const override;

		virtual int GetTasksNum() const override;

		virtual bool GetAssignedTask(FBBManagedConsumer & ManagedConsumer, FBBManagedTask & ManagedTask) const override;

		virtual UIBBTaskQueueIterator * GetIterator() override;

	protected:
		friend class UBBTaskQueueIterator;

		UPROPERTY()
		TArray<FBBManagedTask> ManagedTasks;

		void Sort();

		FORCEINLINE static bool SortTasks(FBBManagedTask const & lhs, FBBManagedTask const & rhs);
		
		int PrioritizeByQueueTime(FBBManagedTask & ManagedTask) const;

		int PrioritizeByProgress(FBBManagedTask & ManagedTask) const;

		int PrioritizeByWorkers(FBBManagedTask & ManagedTask) const;
};

UCLASS(Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBTaskQueueIterator : public UIBBTaskQueueIterator
{
	GENERATED_BODY()

	public:
		UBBTaskQueueIterator();

		virtual void Initialize(UBBTaskQueue * NewTaskQueue, bool Loop);

		virtual bool HasNext() override;

		virtual void Next(FBBManagedTask & NextManagedTask) override;

	protected:
		UPROPERTY()
		UBBTaskQueue * TaskQueue;

		int Index;

		bool LoopTasks;
};