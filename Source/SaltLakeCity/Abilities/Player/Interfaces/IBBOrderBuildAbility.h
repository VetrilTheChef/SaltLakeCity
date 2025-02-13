// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Player/Interfaces/IBBPlayerAbility.h"
#include "IBBOrderBuildAbility.generated.h"

/**
 * 
 */

UCLASS(Abstract)

class SALTLAKECITY_API UIBBOrderBuildAbility : public UIBBPlayerAbility
{
	GENERATED_BODY()
	
	public:
		UIBBOrderBuildAbility() : Super() { };

		virtual bool CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) override { return Super::CommitAbility(Handle, ActorInfo, ActivationInfo, OptionalRelevantTags);  };

		virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override { Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility); };
};