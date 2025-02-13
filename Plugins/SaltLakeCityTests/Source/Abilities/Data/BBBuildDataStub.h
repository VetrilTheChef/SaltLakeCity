// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Data/Interfaces/IBBBuildData.h"
#include "BBBuildDataStub.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable)

class UBBBuildDataStub : public UIBBBuildData
{
	GENERATED_BODY()
	
	public:
		UBBBuildDataStub();

		virtual EBBJob GetJobType() const override;

		virtual FGameplayTag GetEventTag() const override;

		virtual void SetEventTag(FGameplayTag NewEventTag);

		virtual FGameplayEventData * GetEventData() override;

		virtual void SetEventData(FGameplayEventData NewEventData);

		virtual FGameplayTagContainer GetAbilityTags() const override;

		virtual void SetAbilityTags(FGameplayTagContainer NewAbilityTags);

		virtual float GetPrice() const override;

		virtual void SetPrice(float NewPrice) override;

		virtual float GetTime() const override;

		virtual void SetTime(float NewTime) override;

		virtual const TSoftClassPtr<AIBBTargetingActor> GetTargetingClass() const override;

		virtual void SetTargetingClass(TSoftClassPtr<AIBBTargetingActor> NewTargetingClass) override;

		virtual AIBBTargetingActor * GetTargetingActor() const override;

		virtual void SetTargetingActor(AIBBTargetingActor * NewTargeting) override;

		virtual const TArray<FBBBuildablePtr> GetBuildableClasses() const override;

		void SetBuildableClasses(TArray<FBBBuildablePtr> NewBuildableClasses);

		virtual int AddBuildable(TScriptInterface<IBBBuildable> && Buildable) override;

		virtual int RemoveBuildable(TScriptInterface<IBBBuildable> && Buildable) override;

		virtual int GetNumBuildables() const override;

		virtual TScriptInterface<IBBBuildable> GetBuildable(int Index) const override;

		void SetBuildables(TArray<TScriptInterface<IBBBuildable>> NewBuildables);

		virtual TSoftClassPtr<UIBBBuildData> GetBuildDataClass();

		void SetBuildDataClass(TSoftClassPtr<UIBBBuildData> NewBuildDataClass);

	protected:
		UPROPERTY()
		FGameplayTag EventTag;

		UPROPERTY()
		FGameplayEventData EventData;

		UPROPERTY()
		FGameplayTagContainer AbilityTags;

		UPROPERTY()
		TSoftClassPtr<AIBBTargetingActor> TargetingClass;

		UPROPERTY()
		TArray<FBBBuildablePtr> BuildableClasses;

		UPROPERTY()
		AIBBTargetingActor * Targeting;

		UPROPERTY()
		TArray<TScriptInterface<IBBBuildable>> Buildables;

		float Price;

		float Time;

		UPROPERTY()
		TSoftClassPtr<UIBBBuildData> BuildDataClass;
};