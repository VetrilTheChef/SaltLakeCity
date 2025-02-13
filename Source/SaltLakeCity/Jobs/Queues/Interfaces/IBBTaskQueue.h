// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Jobs/Includes/BBManagedTaskStruct.h"
#include "IBBTaskQueue.generated.h"

/**
 *
 */

class UIBBTaskQueueIterator;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBTaskQueue : public UObject
{
	GENERATED_BODY()

	public:
		UIBBTaskQueue() : Super() { };

		virtual void Add(FBBManagedTask & ManagedTask) PURE_VIRTUAL(UIBBTaskQueue::Add, );

		virtual int Remove(FBBManagedTask & ManagedTask) PURE_VIRTUAL(UIBBTaskQueue::Remove, return -1; );

		virtual bool Get(FBBManagedTask & ManagedTask) PURE_VIRTUAL(UIBBTaskQueue::Get, return false; );

		virtual bool HasTask() const PURE_VIRTUAL(UIBBTaskQueue::HasTask, return false; );

		virtual int GetTasksNum() const PURE_VIRTUAL(UIBBTaskQueue::GetTasksNum, return -1; );

		virtual bool GetAssignedTask(FBBManagedConsumer & ManagedConsumer, FBBManagedTask & AssignedTask) const PURE_VIRTUAL(UIBBTaskQueue::GetAssignedTask, return false; );

		virtual UIBBTaskQueueIterator * GetIterator() PURE_VIRTUAL(UIBBTaskQueue::GetIterator, return nullptr; );
};

UCLASS(Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UIBBTaskQueueIterator : public UObject
{
	GENERATED_BODY()

	public:
		UIBBTaskQueueIterator() : Super() {};

		virtual bool HasNext() PURE_VIRTUAL(UIBBTaskQueueIterator::HasNext, return false; );

		virtual void Next(FBBManagedTask & NextManagedTask) PURE_VIRTUAL(UIBBTaskQueueIterator::Next, );
};