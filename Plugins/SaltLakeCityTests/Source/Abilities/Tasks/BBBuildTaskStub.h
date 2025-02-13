// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/Interfaces/IBBBuildTask.h"
#include "BBBuildTaskStub.generated.h"

/**
 * 
 */

class IBBBuildable;

UCLASS(NotBlueprintable)

class UBBBuildTaskStub : public UIBBBuildTask
{
	GENERATED_BODY()
	
	public:
		UBBBuildTaskStub();

		virtual void Decorate(const UIBBAbilityData * NewAbilityData) override;

		virtual EBBJob GetJobType() const override;

		virtual FGameplayTag GetEventTag() const override;

		virtual void SetEventTag(FGameplayTag NewEventTag);

		virtual FGameplayEventData * GetEventData() override;

		virtual void SetEventData(FGameplayEventData NewEventData);

		virtual FGameplayTagContainer GetAbilityTags() const override;

		virtual void SetAbilityTags(FGameplayTagContainer NewAbilityTags);

		virtual float GetProgress() const override;

		virtual void SetProgress(float NewProgress) override;

		virtual float GetPrice() const override;

		void SetPrice(float NewPrice);

		virtual float GetTime() const override;

		void SetTime(float NewTime);

		virtual int GetNumBuildables() const override;

		TScriptInterface<IBBBuildable> GetBuildable(int Index) const;

		void SetBuildables(TArray<TScriptInterface<IBBBuildable>> NewBuildables);

		void Complete();

	protected:

		UPROPERTY()
		FGameplayTag EventTag;

		UPROPERTY()
		FGameplayTagContainer AbilityTags;

		UPROPERTY()
		const UIBBBuildData * BuildData;

		UPROPERTY()
		FGameplayEventData EventData;

		UPROPERTY()
		TArray<TScriptInterface<IBBBuildable>> Buildables;

		float Progress;

		float Price;

		float Time;
};