// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Jobs/Includes/BBJobEnum.h"
#include "Jobs/Includes/BBManagedConsumerStruct.h"
#include "IBBConsumerQueue.generated.h"

/**
 *
 */

class UIBBWorkableQueueIterator;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBConsumerQueue : public UObject
{
	GENERATED_BODY()

	public:
		UIBBConsumerQueue() : Super() { };

		virtual void Initialize(EBBJob NewJob) PURE_VIRTUAL(UIBBConsumerQueue::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBConsumerQueue::Finalize, );

		virtual void Add(FBBManagedConsumer & ManagedConsumer) PURE_VIRTUAL(UIBBConsumerQueue::Add, );

		virtual bool Remove(FBBManagedConsumer & ManagedConsumer) PURE_VIRTUAL(UIBBConsumerQueue::Remove, return false; );

		virtual bool HasConsumer() const PURE_VIRTUAL(UIBBConsumerQueue::HasConsumer, return false; );

		virtual int GetConsumersNum() const PURE_VIRTUAL(UIBBConsumerQueue::GetConsumersNum, return -1; );

		virtual UIBBConsumerQueueIterator * GetIterator() PURE_VIRTUAL(UIBBConsumerQueue::GetIterator, return nullptr; );
};

UCLASS(Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UIBBConsumerQueueIterator : public UObject
{
	GENERATED_BODY()

	public:
		UIBBConsumerQueueIterator() : Super() {};

		virtual bool HasNext() PURE_VIRTUAL(UIBBConsumerQueueIterator::HasNext, return false; );

		virtual void Next(FBBManagedConsumer & NextManagedConsumer) PURE_VIRTUAL(UIBBConsumerQueueIterator::Next, );
};