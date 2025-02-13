// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Jobs/Includes/BBManagedConsumerStruct.h"
#include "BBManagedTaskStruct.generated.h"

/**
*
*/

class UIBBAbilityTask;

USTRUCT(BlueprintType)

struct FBBManagedTask 
{
	GENERATED_BODY()

	public:
		FBBManagedTask()
		{
			AbilityTask = nullptr;
			Consumers.Empty();
			QueueTime = 0;
			Priority = 0;
		}

		FBBManagedTask(UIBBAbilityTask * NewAbilityTask) :
			AbilityTask(NewAbilityTask)
		{
		}

		UPROPERTY()
		UIBBAbilityTask * AbilityTask = nullptr;

		UPROPERTY()
		TArray<FBBManagedConsumer> Consumers;

		int QueueTime = 0;

		int Priority = 0;

		/*friend FORCEINLINE uint32 GetTypeHash(const FBBManagedTask & ManagedTask)
		{
			uint32 HashCode = HashCombine(GetTypeHash(ManagedTask.AbilityData), GetTypeHash(ManagedTask.AbilityTask));
			HashCode = HashCombine(HashCode, GetTypeHash(ManagedTask.Workables));

			return HashCode;
		}*/

		FORCEINLINE bool operator==(const FBBManagedTask & Other) const
		{
			if (AbilityTask == Other.AbilityTask &&
				Consumers == Other.Consumers)
			{
				return true;
			}

			return false;
		}

		FORCEINLINE bool operator<(FBBManagedTask const & Other) const
		{
			return Priority < Other.Priority;
		}

		FORCEINLINE bool operator>(FBBManagedTask const & Other) const
		{
			return Priority > Other.Priority;
		}

		//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBBTaskCompletion, FBBManagedTask &, CompletedTask);

	//private:
		//FBBTaskCompletion OnTaskCompleted;
};