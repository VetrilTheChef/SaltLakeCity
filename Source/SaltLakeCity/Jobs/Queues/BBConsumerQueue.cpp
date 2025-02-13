// SaltLakeCity 4.27

#include "BBConsumerQueue.h"
#include "Actors/Interfaces/IBBWorkable.h"
#include "Actors/Components/Interfaces/IBBWorkComponent.h"

UBBConsumerQueue::UBBConsumerQueue() :
	Super()
{
	Job = EBBJob::None;

	ManagedConsumers.Empty();
}

void UBBConsumerQueue::Initialize(EBBJob NewJob)
{
	Job = NewJob;

	ManagedConsumers.Heapify(UBBConsumerQueue::SortConsumers);
}

void UBBConsumerQueue::Finalize()
{
	ManagedConsumers.Empty();

	Job = EBBJob::None;
}

void UBBConsumerQueue::Add(FBBManagedConsumer & ManagedConsumer)
{
	verifyf(IsValid(ManagedConsumer.Consumer), TEXT("Consumer is invalid."));

	if (!ManagedConsumers.ContainsByPredicate([& ManagedConsumer](FBBManagedConsumer & CurrentManagedConsumer)
		{
			return IsValid(CurrentManagedConsumer.Consumer) && (CurrentManagedConsumer == ManagedConsumer);
		}))
	{
		ManagedConsumers.Emplace(ManagedConsumer);
	}
}

bool UBBConsumerQueue::Remove(FBBManagedConsumer & ManagedConsumer)
{
	if (this->HasConsumer())
	{
		Sort();
		
		ManagedConsumers.Remove(ManagedConsumer);

		return true;
	}

	return false;
}

bool UBBConsumerQueue::HasConsumer() const
{
	return (ManagedConsumers.Num() > 0);
}

int UBBConsumerQueue::GetConsumersNum() const
{
	return ManagedConsumers.Num();
}

UIBBConsumerQueueIterator * UBBConsumerQueue::GetIterator()
{
	UBBConsumerQueueIterator * Iterator = NewObject<UBBConsumerQueueIterator>(this, UBBConsumerQueueIterator::StaticClass());

	verifyf(IsValid(Iterator), TEXT("Consumer Queue Iterator is invalid."));

	Sort();

	Iterator->Initialize(this);

	return Iterator;
}



void UBBConsumerQueue::Sort()
{
	for (FBBManagedConsumer & ManagedConsumer : ManagedConsumers)
	{
		verifyf(IsValid(ManagedConsumer.Consumer), TEXT("Consumer is invalid."));

		ManagedConsumer.Coefficient = SortByJobEfficiency(ManagedConsumer);
	}

	ManagedConsumers.HeapSort(UBBConsumerQueue::SortConsumers);
}

bool UBBConsumerQueue::SortConsumers(FBBManagedConsumer const & lhs, FBBManagedConsumer const & rhs)
{
	return lhs < rhs;
}

float UBBConsumerQueue::SortByJobEfficiency(FBBManagedConsumer & ManagedConsumer) const
{
	verifyf(IsValid(ManagedConsumer.Consumer), TEXT("Consumer is invalid."));

	return ManagedConsumer.Consumer->GetJobEfficiency(Job);
}



UBBConsumerQueueIterator::UBBConsumerQueueIterator() :
	Super()
{
	ConsumerQueue = nullptr;

	Index = 0;
}

void UBBConsumerQueueIterator::Initialize(UBBConsumerQueue * NewConsumerQueue)
{
	verifyf(IsValid(NewConsumerQueue), TEXT("New Consumer Queue is invalid."));

	ConsumerQueue = NewConsumerQueue;
}

bool UBBConsumerQueueIterator::HasNext()
{
	verifyf(IsValid(ConsumerQueue), TEXT("Consumer Queue is invalid."));

	return Index < ConsumerQueue->ManagedConsumers.Num();
}

void UBBConsumerQueueIterator::Next(FBBManagedConsumer & NextManagedConsumer)
{
	verifyf(IsValid(ConsumerQueue), TEXT("Consumer Queue is invalid."));

	NextManagedConsumer = ConsumerQueue->ManagedConsumers[Index++];
}