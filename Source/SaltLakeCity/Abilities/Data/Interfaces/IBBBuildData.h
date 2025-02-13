// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Data/Interfaces/IBBAbilityData.h"
#include "Actors/Interfaces/IBBBuildable.h"
#include "IBBBuildData.generated.h"

/**
 * 
 */

class AIBBTargetingActor;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBBuildData : public UIBBAbilityData
{
	GENERATED_BODY()
	
	public:
		UIBBBuildData() : Super() { };

		virtual EBBJob GetJobType() const PURE_VIRTUAL(UIBBBuildData::GetJobType, return EBBJob::None; );

		virtual FGameplayTag GetEventTag() const override PURE_VIRTUAL(UIBBBuildData::GetEventTag, return FGameplayTag(); );

		virtual FGameplayEventData * GetEventData() override PURE_VIRTUAL(UIBBAbilityData::GetEventData, return nullptr; );
		
		virtual FGameplayTagContainer GetAbilityTags() const override PURE_VIRTUAL(UIBBBuildData::GetAbilityTags, return FGameplayTagContainer(); );

		virtual float GetPrice() const PURE_VIRTUAL(UIBBBuildData::GetPrice, return -1.0f; );

		virtual void SetPrice(float NewPrice) PURE_VIRTUAL(UIBBBuildData::SetPrice, );

		virtual float GetTime() const PURE_VIRTUAL(UIBBBuildData::GetTime, return -1.0f; );

		virtual void SetTime(float NewTime) PURE_VIRTUAL(UIBBBuildData::SetTime, );

		virtual const TSoftClassPtr<AIBBTargetingActor> GetTargetingClass() const PURE_VIRTUAL(UIBBBuildData::GetTargetingClass, return TSoftClassPtr<AIBBTargetingActor>(); );

		virtual void SetTargetingClass(TSoftClassPtr<AIBBTargetingActor> NewTargetingClass) PURE_VIRTUAL(UIBBBuildData::SetTargetingClass, );

		virtual AIBBTargetingActor * GetTargetingActor() const PURE_VIRTUAL(UIBBBuildData::GetTargetingActor, return nullptr; );

		virtual void SetTargetingActor(AIBBTargetingActor * NewTargeting) PURE_VIRTUAL(UIBBBuildData::SetTargetingActor, );
		
		virtual const TArray<FBBBuildablePtr> GetBuildableClasses() const PURE_VIRTUAL(UIBBBuildData::GetBuildableClasses, return TArray<FBBBuildablePtr>(); );

		virtual void SetBuildableClasses(const TArray<FBBBuildablePtr> NewBuildableClasses) PURE_VIRTUAL(UIBBBuildData::SetBuildableClasses, );

		virtual int AddBuildable(TScriptInterface<IBBBuildable> && Buildable) PURE_VIRTUAL(UIBBBuildData::AddBuildable, return -1; );

		virtual int RemoveBuildable(TScriptInterface<IBBBuildable> && Buildable) PURE_VIRTUAL(UIBBBuildData::RemoveBuildable, return -1; );

		virtual int GetNumBuildables() const PURE_VIRTUAL(UIBBBuildData::GetNumBuildables, return -1; );

		virtual TScriptInterface<IBBBuildable> GetBuildable(int Index) const PURE_VIRTUAL(UIBBBuildData::GetBuildable, return nullptr; );
};