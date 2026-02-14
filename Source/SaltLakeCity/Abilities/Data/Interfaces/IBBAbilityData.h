// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Jobs/Includes/BBJobEnum.h"
#include "IBBAbilityData.generated.h"

/**
 * 
 */

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBAbilityData : public UObject
{
	GENERATED_BODY()
	
	public:
		UIBBAbilityData() : Super() { };

		virtual EBBJob GetJobType() const
			PURE_VIRTUAL(UIBBAbilityData::GetJobType, return EBBJob::None; );

		virtual FGameplayTag GetEventTag() const
			PURE_VIRTUAL(UIBBAbilityData::GetEventTag, return FGameplayTag(); );

		virtual FGameplayEventData * GetEventData()
			PURE_VIRTUAL(UIBBAbilityData::GetEventData, return nullptr; );

		virtual FGameplayTagContainer GetAbilityTags() const
			PURE_VIRTUAL(UIBBAbilityData::GetAbilityTags, return FGameplayTagContainer(); );
};