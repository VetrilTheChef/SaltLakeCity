// SaltLakeCity 4.26

#include "BBPlayerAbilityStub.h"

UBBPlayerAbilityStub::UBBPlayerAbilityStub() :
	Super()
{
	InstancingPolicy = TEnumAsByte<EGameplayAbilityInstancingPolicy::Type>(EGameplayAbilityInstancingPolicy::InstancedPerActor);

	ActivationCalls = 0;
}

void UBBPlayerAbilityStub::SetActivationRequiredTags(FGameplayTagContainer NewActivationRequiredTags)
{
	ActivationRequiredTags = NewActivationRequiredTags;
}

void UBBPlayerAbilityStub::SetInstancingPolicy(EGameplayAbilityInstancingPolicy::Type NewInstancingPolicy)
{
	InstancingPolicy = TEnumAsByte<EGameplayAbilityInstancingPolicy::Type>(NewInstancingPolicy);
}

bool UBBPlayerAbilityStub::CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags)
{
	return Super::CommitAbility(Handle, ActorInfo, ActivationInfo, OptionalRelevantTags);
}

void UBBPlayerAbilityStub::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData * TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ActivationCalls++;

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

int UBBPlayerAbilityStub::GetNumActivations()
{
	return ActivationCalls;
}