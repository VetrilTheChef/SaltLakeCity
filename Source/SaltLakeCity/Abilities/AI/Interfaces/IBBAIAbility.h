// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Interfaces/IBBAbility.h"
#include "IBBAIAbility.generated.h"

/**
 * 
 */

class UBehaviorTree;
class UIBBAbilityTask;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBAIAbility : public UIBBAbility
{
	GENERATED_BODY()
	
	public:
		UIBBAIAbility() : Super() { };

		virtual bool CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer * OptionalRelevantTags = nullptr) override { return Super::CommitAbility(Handle, ActorInfo, ActivationInfo, OptionalRelevantTags); };
		
		virtual const FName GetTaskName() const PURE_VIRTUAL(UIBBAIAbility::GetTaskName, return FName(); );

		virtual const UIBBAbilityTask * GetTask() const PURE_VIRTUAL(UIBBAIAbility::GetTask, return nullptr; );

		virtual const UBehaviorTree * GetBehaviorTree() const PURE_VIRTUAL(UIBBAIAbility::GetBehaviorTree, return nullptr; );
};