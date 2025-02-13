// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Jobs/Includes/BBManagedConsumerStruct.h"
#include "Jobs/Queues/Interfaces/IBBConsumerQueue.h"
#include "BBConsumerQueue.generated.h"

/**
 *
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBConsumerQueue : public UIBBConsumerQueue
{
	GENERATED_BODY()

	public:
		UBBConsumerQueue();

		virtual void Initialize(EBBJob NewJob) override;

		virtual void Finalize() override;

		virtual void Add(FBBManagedConsumer & ManagedConsumer) override;

		virtual bool Remove(FBBManagedConsumer & ManagedConsumer) override;

		virtual bool HasConsumer() const override;

		virtual int GetConsumersNum() const override;

		virtual UIBBConsumerQueueIterator * GetIterator() override;

	protected:
		friend class UBBConsumerQueueIterator;

		UPROPERTY()
		TArray<FBBManagedConsumer> ManagedConsumers;

		EBBJob Job;

		void Sort();

		FORCEINLINE static bool SortConsumers(FBBManagedConsumer const & lhs, FBBManagedConsumer const & rhs);

		float SortByJobEfficiency(FBBManagedConsumer & ManagedConsumer) const;
};

UCLASS(Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBConsumerQueueIterator : public UIBBConsumerQueueIterator
{
	GENERATED_BODY()

	public:
		UBBConsumerQueueIterator();

		virtual void Initialize(UBBConsumerQueue * NewWorkerQueue);

		virtual bool HasNext() override;

		virtual void Next(FBBManagedConsumer & NextManagedWorker) override;

	protected:
		UPROPERTY()
		UBBConsumerQueue * ConsumerQueue;

		int Index;
};