// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Player/Interfaces/IBBOrderBuildAbility.h"
#include "BBOrderBuildAbilityStub.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable)

class UBBOrderBuildAbilityStub : public UIBBOrderBuildAbility
{
	GENERATED_BODY()
	
	public:
		UBBOrderBuildAbilityStub();

		virtual bool CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) override;

		int GetNumActivations();

	protected:
		int ActivationCalls;
};