// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Interfaces/IBBAbility.h"
#include "BBAbilityStub.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable)

class UBBAbilityStub : public UIBBAbility
{
	GENERATED_BODY()

	public:
		UBBAbilityStub();
		
		virtual bool CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) override;
};