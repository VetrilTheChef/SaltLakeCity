// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/Interfaces/IBBAbilityTask.h"
#include "IBBBuildTask.generated.h"

/**
 * 
 */

class IBBBuildable;
class UIBBBuildData;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBBuildTask : public UIBBAbilityTask
{
	GENERATED_BODY()
	
	public:
		UIBBBuildTask() : Super() { };

		virtual void PostInitProperties() override { Super::PostInitProperties(); }
		
		virtual void Decorate(const UIBBAbilityData * NewAbilityData) override PURE_VIRTUAL(UIBBBuildTask::Decorate, );

		virtual const UIBBAbilityData * GetAbilityData() const PURE_VIRTUAL(UIBBBuildTask::GetAbilityData, return nullptr; );

		virtual EBBJob GetJobType() const PURE_VIRTUAL(UIBBBuildTask::GetJobType, return EBBJob::None; );

		virtual FGameplayTag GetEventTag() const override PURE_VIRTUAL(UIBBBuildTask::GetEventTag, return FGameplayTag(); );

		virtual FGameplayEventData * GetEventData() override PURE_VIRTUAL(UIBBBuildTask::GetEventData, return nullptr; );
		
		virtual FGameplayTagContainer GetAbilityTags() const override PURE_VIRTUAL(UIBBBuildTask::GetAbilityTags, return FGameplayTagContainer(); );

		virtual float GetProgress() const override PURE_VIRTUAL(UIBBBuildTask::GetProgress, return -1.0f; );

		virtual void SetProgress(float NewProgress) override PURE_VIRTUAL(UIBBBuildTask::SetProgress, );

		UFUNCTION(BlueprintCallable, Category = "Build Task")
		virtual float GetPrice() const PURE_VIRTUAL(UIBBBuildTask::GetPrice, return -1.0f; );

		UFUNCTION(BlueprintCallable, Category = "Build Task")
		virtual float GetTime() const PURE_VIRTUAL(UIBBBuildTask::GetTime, return -1.0f; );

		UFUNCTION(BlueprintCallable, Category = "Build Task")
		virtual int GetNumBuildables() const PURE_VIRTUAL(UIBBBuildTask::GetNumBuildables, return -1; );

		UFUNCTION(BlueprintCallable, Category = "Build Task")
		virtual TScriptInterface<IBBBuildable> GetBuildable(int Index) const PURE_VIRTUAL(UIBBBuildTask::GetBuildable, return TScriptInterface<IBBBuildable>(); );

		FORCEINLINE virtual bool operator==(const UIBBAbilityData * Other) const override PURE_VIRTUAL(UIBBBuildTask::operator==, return false; );
};