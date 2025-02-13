// SaltLakeCity 4.26

#include "BBOrderBuildAbilityStub.h"

UBBOrderBuildAbilityStub::UBBOrderBuildAbilityStub() :
	Super()
{
	ActivationCalls = 0;
}

bool UBBOrderBuildAbilityStub::CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags)
{
	ActivationCalls++;

	if (Super::CommitAbility(Handle, ActorInfo, ActivationInfo, OptionalRelevantTags))
	{
		Super::EndAbility(Handle, ActorInfo, ActivationInfo, true, false);

		return true;
	}

	return false;
}

int UBBOrderBuildAbilityStub::GetNumActivations()
{
	return ActivationCalls;
}