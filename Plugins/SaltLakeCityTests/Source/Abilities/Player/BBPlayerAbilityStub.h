// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Player/Interfaces/IBBPlayerAbility.h"
#include "BBPlayerAbilityStub.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable)

class UBBPlayerAbilityStub : public UIBBPlayerAbility
{
	GENERATED_BODY()
	
	public:
		UBBPlayerAbilityStub();

		void SetActivationRequiredTags(FGameplayTagContainer NewTagContainer);

		void SetInstancingPolicy(EGameplayAbilityInstancingPolicy::Type NewInstancingPolicy);

		virtual bool CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) override;

		virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData * TriggerEventData) override;
		
		int GetNumActivations();

	protected:
		int ActivationCalls;
};