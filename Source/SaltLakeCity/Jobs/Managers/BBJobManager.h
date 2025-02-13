// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Attributes/Includes/BBSkillEnum.h"
#include "Jobs/Includes/BBManagedTaskStruct.h"
#include "Jobs/Includes/BBManagedConsumerStruct.h"
#include "Jobs/Managers/Interfaces/IBBJobManager.h"
#include "BBJobManager.generated.h"

/**
 * 
 */

class UIBBAbilityTask;
class UIBBConsumerQueue;
class UIBBTaskQueue;
class UIBBWorkComponent;

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBJobManager : public UIBBJobManager
{
	GENERATED_BODY()
	
	public:
		UBBJobManager();

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
		UPROPERTY(Category = "Settings", EditAnywhere, BlueprintReadWrite)
		EBBJob Job;

		UPROPERTY(Category = "Settings", EditAnywhere, BlueprintReadWrite)
		TSoftClassPtr<UIBBAbilityTask> TaskClass;

		UPROPERTY(Category = "Settings", EditAnywhere, BlueprintReadWrite)
		TSoftClassPtr<UIBBTaskQueue> TaskQueueClass;

		UPROPERTY(Category = "Settings", EditAnywhere, BlueprintReadWrite)
		TSoftClassPtr<UIBBConsumerQueue> ConsumerQueueClass;

		UPROPERTY()
		UIBBTaskQueue * TaskQueue;

		UPROPERTY()
		UIBBConsumerQueue * ConsumerQueue;

		void CreateQueues();

		void CreateTaskQueue();

		void CreateConsumerQueue();

		void DestroyQueues();

		void DestroyTaskQueue();

		void DestroyConsumerQueue();

		void SubscribeToQueues();

		void UnsubscribeFromQueues();

		virtual void Manage();

		bool FindManagedTask(FBBManagedTask & ManagedTask, const UIBBAbilityTask * Task) const;

		bool FindManagedConsumer(FBBManagedConsumer & ManagedConsumer, const UIBBWorkComponent * Consumer) const;

		bool AssignTask(FBBManagedConsumer & ManagedConsumer, FBBManagedTask & ManagedTask);

		bool UnassignTask(FBBManagedConsumer & ManagedConsumer, FBBManagedTask & ManagedTask);

		bool AssignConsumer(FBBManagedConsumer & ManagedConsumer, FBBManagedTask & ManagedTask);

		bool UnassignConsumer(FBBManagedConsumer & ManagedConsumer, FBBManagedTask & ManagedTask);
};