// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Abilities/AI/Interfaces/IBBAIAbility.h"
#include "IBBSatisfyNeedAbility.generated.h"

/**
 * 
 */

UCLASS(Abstract)

class SALTLAKECITY_API UIBBSatisfyNeedAbility : public UIBBAIAbility
{
	GENERATED_BODY()
	
	public:
		UIBBSatisfyNeedAbility() : Super() { };

		virtual bool CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) override { return Super::CommitAbility(Handle, ActorInfo, ActivationInfo, OptionalRelevantTags); };
};