// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/Interfaces/IBBBuildTask.h"
#include "BBBuildTask.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBBuildTask : public UIBBBuildTask
{
	GENERATED_BODY()
	
	public:
		UBBBuildTask();

		virtual void PostInitProperties() override;

		virtual void Decorate(const UIBBAbilityData * NewAbilityData) override;
		
		virtual const UIBBAbilityData * GetAbilityData() const override;
		
		virtual EBBJob GetJobType() const override;

		virtual FGameplayTag GetEventTag() const override;

		virtual FGameplayEventData * GetEventData() override;

		virtual FGameplayTagContainer GetAbilityTags() const override;

		virtual float GetProgress() const override;

		virtual void SetProgress(float NewProgress) override;

		virtual float GetPrice() const override;

		virtual float GetTime() const override;

		int GetNumBuildables() const override;

		TScriptInterface<IBBBuildable> GetBuildable(int Index) const override;

		FORCEINLINE virtual bool operator==(const UIBBAbilityData * Other) const override;

	protected:
		UPROPERTY(EditDefaultsOnly, Category = "Tags", meta = (Categories = "AbilityTagCategory"))
		FGameplayTag EventTag;

		UPROPERTY(EditDefaultsOnly, Category = "Tags", meta = (Categories = "AbilityTagCategory"))
		FGameplayTagContainer AbilityTags;

		UPROPERTY()
		const UIBBBuildData * BuildData;

		FGameplayEventData EventData;

		float Progress;

		void CompleteTask();
};