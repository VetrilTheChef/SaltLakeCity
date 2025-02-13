// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Abilities/AI/Interfaces/IBBBuildAbility.h"
#include "BBBuildAbility.generated.h"

/**
 * 
 */

class UIBBAIAbilityComponent;
class UIBBBuildTask;

UCLASS(Abstract)

class SALTLAKECITY_API UBBBuildAbility : public UIBBBuildAbility
{
	GENERATED_BODY()
	
	public:
		UBBBuildAbility();

		virtual bool CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) override;

		virtual const FName GetTaskName() const override;

		virtual const UIBBAbilityTask * GetTask() const override;

		virtual const UBehaviorTree * GetBehaviorTree() const override;

	protected:
		UPROPERTY(Category = "Behavior Tree", EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		TSoftObjectPtr<UBehaviorTree> BehaviorTree;

		UPROPERTY(Category = "Blackboard", EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		FName TaskName;

		UPROPERTY()
		UIBBAIAbilityComponent * AIAbilityComponent;

		UPROPERTY()
		UIBBBuildTask * BuildTask;

		virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData * TriggerEventData) override;

		virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

		void RunBehaviorTree();

		UFUNCTION()
		void CompleteTask(UIBBAbilityTask * CompletedTask);
};