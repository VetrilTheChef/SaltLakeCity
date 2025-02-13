// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Jobs/Includes/BBJobEnum.h"
#include "IBBAbilityTask.generated.h"

/**
 * 
 */

class UIBBAbilityData;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBAbilityTask : public UObject
{
	GENERATED_BODY()
	
	public:
		UIBBAbilityTask() : Super() { };

		virtual void Decorate(const UIBBAbilityData * NewAbilityData) PURE_VIRTUAL(UIBBAbilityTask::Decorate, );

		virtual const UIBBAbilityData * GetAbilityData() const PURE_VIRTUAL(UIBBAbilityTask::GetAbilityData, return nullptr; );

		virtual EBBJob GetJobType() const PURE_VIRTUAL(UIBBAbilityTask::GetJobType, return EBBJob::None; );

		virtual FGameplayTag GetEventTag() const PURE_VIRTUAL(UIBBAbilityTask::GetEventTag, return FGameplayTag(); );

		virtual FGameplayEventData * GetEventData() PURE_VIRTUAL(UIBBAbilityTask::GetEventData, return nullptr; );

		virtual FGameplayTagContainer GetAbilityTags() const PURE_VIRTUAL(UIBBAbilityTask::GetAbilityTags, return FGameplayTagContainer(); );

		UFUNCTION(BlueprintCallable, Category = "Ability Task")
		virtual float GetProgress() const PURE_VIRTUAL(UIBBAbilityTask::GetProgress, return -1.0f; );

		UFUNCTION(BlueprintCallable, Category = "Ability Task")
		virtual void SetProgress(float NewProgress) PURE_VIRTUAL(UIBBAbilityTask::SetProgress, );

		DECLARE_EVENT_OneParam(UIBBAbilityTask, FBBTaskCompleted, UIBBAbilityTask *);

		virtual FBBTaskCompleted & OnTaskCompleted() { return TaskCompleted; };

		FORCEINLINE virtual bool operator==(const UIBBAbilityData * Other) const PURE_VIRTUAL(UIBBAbilityTask::operator==, return false; );

	protected:
		FBBTaskCompleted TaskCompleted;
};