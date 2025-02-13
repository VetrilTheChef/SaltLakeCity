// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Data/Interfaces/IBBBuildData.h"
#include "BBBuildData.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBBuildData : public UIBBBuildData
{
	GENERATED_BODY()
	
	public:
		UBBBuildData();

		virtual void PostInitProperties() override;
		
		virtual EBBJob GetJobType() const override;

		virtual FGameplayTag GetEventTag() const override;

		virtual FGameplayEventData * GetEventData() override;

		virtual FGameplayTagContainer GetAbilityTags() const override;

		virtual float GetPrice() const override;

		virtual void SetPrice(float NewPrice) override;

		virtual float GetTime() const override;

		virtual void SetTime(float NewTime) override;

		virtual const TSoftClassPtr<AIBBTargetingActor> GetTargetingClass() const override;

		virtual void SetTargetingClass(TSoftClassPtr<AIBBTargetingActor> NewTargetingClass) override;

		virtual AIBBTargetingActor * GetTargetingActor() const override;

		virtual void SetTargetingActor(AIBBTargetingActor * NewTargeting) override;

		virtual const TArray<FBBBuildablePtr> GetBuildableClasses() const override;

		virtual void SetBuildableClasses(const TArray<FBBBuildablePtr> NewBuildableClasses) override;

		virtual int AddBuildable(TScriptInterface<IBBBuildable> && Buildable) override;

		virtual int RemoveBuildable(TScriptInterface<IBBBuildable> && Buildable) override;

		int GetNumBuildables() const override;

		TScriptInterface<IBBBuildable> GetBuildable(int Index) const override;

	protected:
		UPROPERTY(EditDefaultsOnly, Category = "Tags", meta = (Categories = "AbilityTagCategory"))
		FGameplayTag EventTag;

		UPROPERTY(EditDefaultsOnly, Category = "Tags", meta = (Categories = "AbilityTagCategory"))
		FGameplayTagContainer AbilityTags;

		UPROPERTY(Category = "Targeting", EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		TSoftClassPtr<AIBBTargetingActor> TargetingClass;

		UPROPERTY()
		TArray<FBBBuildablePtr> BuildableClasses;

		UPROPERTY()
		AIBBTargetingActor * Targeting;
		
		UPROPERTY()
		TArray<TScriptInterface<IBBBuildable>> Buildables;

		UPROPERTY()
		FGameplayEventData EventData;

		float Price;

		float Time;
};