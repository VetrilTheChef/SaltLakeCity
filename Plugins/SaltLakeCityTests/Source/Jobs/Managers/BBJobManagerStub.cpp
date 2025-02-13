// SaltLakeCity 4.27

#include "BBJobManagerStub.h"
#include "Abilities/Data/Interfaces/IBBAbilityData.h"

UBBJobManagerStub::UBBJobManagerStub() :
	Super()
{
	AssignedConsumers.Empty();
	UnassignedConsumers.Empty();
	AssignedTasks.Empty();
	UnassignedTasks.Empty();
}

void UBBJobManagerStub::Initialize()
{
}

void UBBJobManagerStub::Finalize()
{
}

void UBBJobManagerStub::AddTask(const UIBBAbilityData * AbilityData)
{
	if (IsValid(AbilityData))
	{
		UnassignedTasks.Emplace(AbilityData);

		Manage();
	}
}

void UBBJobManagerStub::RemoveTask(const UIBBAbilityData * AbilityData)
{
	if (IsValid(AbilityData))
	{
		AssignedTasks.Remove(AbilityData);
		UnassignedTasks.Remove(AbilityData);

		Manage();
	}
}

int UBBJobManagerStub::GetTasksNum()
{
	return AssignedTasks.Num() + UnassignedTasks.Num();
}

void UBBJobManagerStub::AddConsumer(UIBBWorkComponent * Consumer)
{
	verifyf(IsValid(Consumer), TEXT("Consumer is invalid."));

	FBBManagedConsumer ManagedConsumer = FBBManagedConsumer();
	verifyf(!FindAvailableManagedConsumer(ManagedConsumer, Consumer), TEXT("Consumer was already added."));

	ManagedConsumer.Consumer = Consumer;

	UnassignedConsumers.Emplace(ManagedConsumer);

	Manage();
}

void UBBJobManagerStub::RemoveConsumer(UIBBWorkComponent * Consumer)
{
	FBBManagedConsumer ManagedConsumer;

	if (FindAvailableManagedConsumer(ManagedConsumer, Consumer))
	{
		UnassignedConsumers.Remove(ManagedConsumer);
	}

	if (FindAssignedManagedConsumer(ManagedConsumer, Consumer))
	{
		AssignedConsumers.Remove(ManagedConsumer);
	}

	Manage();
}

int UBBJobManagerStub::GetConsumersNum()
{
	return -1;
}

void UBBJobManagerStub::CompleteTask(UIBBAbilityTask * AbilityTask)
{
	CompletedTasks.Emplace(AbilityTask);

	Manage();
}



void UBBJobManagerStub::Manage()
{
	Sort();
}

void UBBJobManagerStub::Sort()
{
}

bool UBBJobManagerStub::FindAssignedManagedConsumer(FBBManagedConsumer & ManagedConsumer, UIBBWorkComponent * Consumer)
{
	for (FBBManagedConsumer & AssignedConsumer : AssignedConsumers)
	{
		if (AssignedConsumer.Consumer == Consumer)
		{
			ManagedConsumer = AssignedConsumer;

			return true;
		}
	}

	return false;
}

bool UBBJobManagerStub::FindAvailableManagedConsumer(FBBManagedConsumer & ManagedConsumer, UIBBWorkComponent * Consumer)
{
	for (FBBManagedConsumer & UnassignedConsumer : UnassignedConsumers)
	{
		if (UnassignedConsumer.Consumer == Consumer)
		{
			ManagedConsumer = UnassignedConsumer;

			return true;
		}
	}

	return false;
}

void UBBJobManagerStub::AssignTask(FBBManagedConsumer & ManagedConsumer, UIBBAbilityTask * AbilityTask)
{
	verifyf(IsValid(ManagedConsumer.Consumer), TEXT("Consumer is invalid."));

	ManagedConsumer.Consumer->AssignTask(AbilityTask);
	ManagedConsumer.Consumer->StartTask();
}

UIBBAbilityTask * UBBJobManagerStub::UnassignTask(FBBManagedConsumer & ManagedConsumer)
{
	verifyf(IsValid(ManagedConsumer.Consumer), TEXT("Consumer is invalid."));

	if (ManagedConsumer.Consumer->IsWorking())
	{
		ManagedConsumer.Consumer->StopTask();

		return ManagedConsumer.Consumer->UnassignTask();
	}

	return nullptr;
}

void UBBJobManagerStub::AssignConsumer(FBBManagedConsumer & ManagedConsumer)
{
	verifyf(IsValid(ManagedConsumer.Consumer), TEXT("Consumer is invalid."));

	UnassignedConsumers.Remove(ManagedConsumer);
	AssignedConsumers.Emplace(ManagedConsumer);
}

void UBBJobManagerStub::UnassignConsumer(FBBManagedConsumer & ManagedConsumer)
{
	verifyf(IsValid(ManagedConsumer.Consumer), TEXT("Consumer is invalid."));

	AssignedConsumers.Remove(ManagedConsumer);
	UnassignedConsumers.Emplace(ManagedConsumer);
}