// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Abilities/AI/Interfaces/IBBAIAbility.h"
#include "IBBBuildAbility.generated.h"

/**
 * 
 */

UCLASS(Abstract)

class SALTLAKECITY_API UIBBBuildAbility : public UIBBAIAbility
{
	GENERATED_BODY()
	
	public:
		UIBBBuildAbility() : Super() { };

		virtual bool CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) override { return Super::CommitAbility(Handle, ActorInfo, ActivationInfo, OptionalRelevantTags); };

		virtual const FName GetTaskName() const override PURE_VIRTUAL(UIBBBuildAbility::GetTaskName, return FName(); );

		virtual const UIBBAbilityTask * GetTask() const override PURE_VIRTUAL(UIBBBuildAbility::GetTask, return nullptr; );

		virtual const UBehaviorTree * GetBehaviorTree() const override PURE_VIRTUAL(UIBBBuildAbility::GetBehaviorTree, return nullptr; );
};