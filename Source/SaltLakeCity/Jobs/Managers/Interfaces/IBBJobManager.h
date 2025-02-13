// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IBBJobManager.generated.h"

/**
 * 
 */

class UIBBAbilityData;
class UIBBAbilityTask;
class UIBBWorkComponent;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBJobManager : public UObject
{
	GENERATED_BODY()
	
	public:
		UIBBJobManager() : Super() { };

		virtual void Initialize() PURE_VIRTUAL(UIBBJobManager::Initialize, );
		
		virtual void Finalize() PURE_VIRTUAL(UIBBJobManager::Finalize, );

		virtual void AddTask(const UIBBAbilityData * AbilityData) PURE_VIRTUAL(UIBBJobManager::AddTask, );

		virtual void RemoveTask(const UIBBAbilityData * AbilityData) PURE_VIRTUAL(UIBBJobManager::RemoveTask, );

		virtual int GetTasksNum() PURE_VIRTUAL(UIBBJobManager::GetTasksNum, return -1; );

		virtual int GetTasks(TArray<UIBBAbilityTask *> & Tasks) const PURE_VIRTUAL(UIBBJobManager::GetTasks, return -1; );

		virtual void AddConsumer(UIBBWorkComponent * WorkComponent) PURE_VIRTUAL(UIBBJobManager::AddConsumer, );

		virtual void RemoveConsumer(UIBBWorkComponent * WorkComponent) PURE_VIRTUAL(UIBBJobManager::RemoveConsumer, );

		virtual int GetConsumersNum() PURE_VIRTUAL(UIBBJobManager::GetWorkablesNum, return -1; );

		virtual int GetTaskConsumers(TArray<UIBBWorkComponent *> & Consumers, UIBBAbilityTask * AbilityTask) PURE_VIRTUAL(UIBBJobManager::GetTaskConsumers, return -1; );

		UFUNCTION()
		virtual void CompleteTask(UIBBAbilityTask * AbilityTask) PURE_VIRTUAL(UIBBJobManager::CompleteTask, );
};