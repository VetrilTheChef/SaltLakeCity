// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Abilities/AI/Interfaces/IBBBuildAbility.h"
#include "BBBuildAbilityStub.generated.h"

/**
 * 
 */

class UIBBBuildTask;

UCLASS(NotBlueprintable)

class UBBBuildAbilityStub : public UIBBBuildAbility
{
	GENERATED_BODY()
	
	public:
		UBBBuildAbilityStub();

		virtual const FName GetTaskName() const override;

		virtual const UIBBAbilityTask * GetTask() const override;

		virtual const UBehaviorTree * GetBehaviorTree() const override;

		int GetNumCompleteTasks() const;

	protected:

		UPROPERTY()
		UIBBBuildTask * BuildTask;

		FName TaskName;

		int CompleteTaskCalls;

		virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData * TriggerEventData) override;

		virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
		
		UFUNCTION()
		void CompleteTask(UIBBAbilityTask * CompletedTask);
};