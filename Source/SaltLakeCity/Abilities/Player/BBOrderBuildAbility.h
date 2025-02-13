// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Player/Interfaces/IBBOrderBuildAbility.h"
#include "BBOrderBuildAbility.generated.h"

/**
 * 
 */

class AIBBTargetingActor;
class UAbilityTask_WaitTargetData;
class UBBBuildProducer;
class UIBBBuildData;

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBOrderBuildAbility : public UIBBOrderBuildAbility
{
	GENERATED_BODY()
	
	public:
		UBBOrderBuildAbility();

		virtual bool CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) override;

		virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;

	protected:
		UPROPERTY()
		UIBBPlayerAbilityComponent * PlayerAbilityComponent;
		
		UPROPERTY()
		UIBBBuildData * AbilityData;

		UPROPERTY()
		UAbilityTask_WaitTargetData * WaitTargetDataTask;

		virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData * TriggerEventData) override;
		
		virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
		
		void WaitForTargetData();

		UFUNCTION()
		void TargetingFinish(const FGameplayAbilityTargetDataHandle & Data);

		UFUNCTION()
		void TargetingCancel(const FGameplayAbilityTargetDataHandle & Data);
};