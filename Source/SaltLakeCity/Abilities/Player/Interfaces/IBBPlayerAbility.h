// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Interfaces/IBBAbility.h"
#include "IBBPlayerAbility.generated.h"

/**
 * 
 */

class UIBBPlayerAbilityComponent;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBPlayerAbility : public UIBBAbility
{
	GENERATED_BODY()
	
	public:
		UIBBPlayerAbility() : Super() { };
		
		virtual bool CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) override { return Super::CommitAbility(Handle, ActorInfo, ActivationInfo, OptionalRelevantTags); };
};