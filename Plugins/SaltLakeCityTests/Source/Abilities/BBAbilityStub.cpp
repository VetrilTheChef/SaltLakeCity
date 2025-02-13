// SaltLakeCity 4.25

#include "BBAbilityStub.h"

UBBAbilityStub::UBBAbilityStub() :
	Super()
{
}

bool UBBAbilityStub::CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags)
{
	return Super::CommitAbility(Handle, ActorInfo, ActivationInfo, OptionalRelevantTags);
}