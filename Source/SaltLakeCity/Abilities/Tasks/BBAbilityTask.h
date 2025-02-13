// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/Interfaces/IBBAbilityTask.h"
#include "BBAbilityTask.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBAbilityTask : public UIBBAbilityTask
{
	GENERATED_BODY()
	
	public:
		UBBAbilityTask();

		virtual void Decorate(const UIBBAbilityData * NewAbilityData) override;

		virtual const UIBBAbilityData * GetAbilityData() const override;

		virtual EBBJob GetJobType() const override;

		virtual FGameplayTag GetEventTag() const override;

		virtual FGameplayEventData * GetEventData() override;

		virtual FGameplayTagContainer GetAbilityTags() const override;

		virtual float GetProgress() const override;

		virtual void SetProgress(float NewProgress) override;

		FORCEINLINE virtual bool operator==(const UIBBAbilityData * Other) const override;

	protected:
		UPROPERTY(EditDefaultsOnly, Category = "Tags", meta = (Categories = "AbilityTagCategory"))
		FGameplayTag EventTag;

		UPROPERTY(EditDefaultsOnly, Category = "Tags", meta = (Categories = "AbilityTagCategory"))
		FGameplayTagContainer AbilityTags;

		UPROPERTY(EditDefaultsOnly, Category = "Job")
		EBBJob Job;
		
		UPROPERTY()
		const UIBBAbilityData * AbilityData;

		FGameplayEventData EventData;

		float Progress;

		void CompleteTask();
};