// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Data/Interfaces/IBBAbilityData.h"
#include "BBAbilityDataStub.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable)

class UBBAbilityDataStub : public UIBBAbilityData
{
	GENERATED_BODY()
	
	public:
		UBBAbilityDataStub();

		virtual EBBJob GetJobType() const override;

		virtual FGameplayTag GetEventTag() const override;

		virtual void SetEventTag(FGameplayTag NewEventTag);

		virtual FGameplayEventData * GetEventData() override;

		virtual void SetEventData(FGameplayEventData NewEventData);

		virtual FGameplayTagContainer GetAbilityTags() const override;

		virtual void SetAbilityTags(FGameplayTagContainer NewAbilityTags);

	protected:
		UPROPERTY()
		FGameplayTag EventTag;

		UPROPERTY()
		FGameplayEventData EventData;

		UPROPERTY()
		FGameplayTagContainer AbilityTags;
};