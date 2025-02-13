// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Jobs/Includes/BBManagedConsumerStruct.h"
#include "Jobs/Managers/Interfaces/IBBJobManager.h"
#include "BBJobManagerStub.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class UBBJobManagerStub : public UIBBJobManager
{
	GENERATED_BODY()
	
	public:
		UBBJobManagerStub();

		virtual void Initialize() override;

		virtual void Finalize() override;

		virtual void AddTask(const UIBBAbilityData * AbilityData) override;

		virtual void RemoveTask(const UIBBAbilityData * AbilityData) override;

		virtual int GetTasksNum() override;

		virtual void AddConsumer(UIBBWorkComponent * Consumer) override;

		virtual void RemoveConsumer(UIBBWorkComponent * Consumer) override;

		virtual int GetConsumersNum() override;

		virtual void CompleteTask(UIBBAbilityTask * AbilityTask) override;

	protected:
		UPROPERTY()
		TArray<FBBManagedConsumer> AssignedConsumers;

		UPROPERTY()
		TArray<FBBManagedConsumer> UnassignedConsumers;

		UPROPERTY()
		TArray<const UIBBAbilityData *> AssignedTasks;

		UPROPERTY()
		TArray<const UIBBAbilityData *> UnassignedTasks;

		UPROPERTY()
		TArray<UIBBAbilityTask *> CompletedTasks;

		virtual void Manage();

		virtual void Sort();

		bool FindAssignedManagedConsumer(FBBManagedConsumer & ManagedConsumer, UIBBWorkComponent * Consumer);

		bool FindAvailableManagedConsumer(FBBManagedConsumer & ManagedConsumer, UIBBWorkComponent * Consumer);

		void AssignTask(FBBManagedConsumer & ManagedConsumer, UIBBAbilityTask * AbilityTask);

		UIBBAbilityTask * UnassignTask(FBBManagedConsumer & ManagedConsumer);

		void AssignConsumer(FBBManagedConsumer & ManagedConsumer);

		void UnassignConsumer(FBBManagedConsumer & ManagedConsumer);
};