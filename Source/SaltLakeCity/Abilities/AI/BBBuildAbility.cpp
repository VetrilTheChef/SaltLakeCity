// SaltLakeCity 4.26

#include "BBBuildAbility.h"
#include "Abilities/Tasks/Interfaces/IBBBuildTask.h"
#include "Actors/Components/Interfaces/IBBAIAbilityComponent.h"
#include "Actors/Interfaces/IBBBuildable.h"
#include "BehaviorTree/BehaviorTree.h"

UBBBuildAbility::UBBBuildAbility() :
	Super()
{
	AIAbilityComponent = nullptr;

	TaskName = FName("");
	BuildTask = nullptr;
}

bool UBBBuildAbility::CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags)
{
	return Super::CommitAbility(Handle, ActorInfo, ActivationInfo, OptionalRelevantTags);
}

const FName UBBBuildAbility::GetTaskName() const
{
	return TaskName;
}

const UIBBAbilityTask * UBBBuildAbility::GetTask() const
{
	return BuildTask;
}

const UBehaviorTree * UBBBuildAbility::GetBehaviorTree() const
{
	return BehaviorTree.LoadSynchronous();
}



void UBBBuildAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData * TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AIAbilityComponent = Cast<UIBBAIAbilityComponent>(GetAbilitySystemComponentFromActorInfo());

	verifyf(IsValid(AIAbilityComponent), TEXT("AI Ability Component is invalid."));
	
	// No straightforward way to pass the task data while keeping it non-const
	// So, const_cast

	BuildTask = const_cast<UIBBBuildTask *>(Cast<UIBBBuildTask>(TriggerEventData->OptionalObject));

	verifyf(IsValid(BuildTask), TEXT("Build Task is invalid."));

	BuildTask->OnTaskCompleted().AddUObject(this, & UBBBuildAbility::CompleteTask);

	RunBehaviorTree();
}

void UBBBuildAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (!bWasCancelled)
	{
		verifyf(IsValid(AIAbilityComponent), TEXT("AI Ability Component is invalid."));

		AIAbilityComponent->StopTask(BuildTask);
	}
}

void UBBBuildAbility::RunBehaviorTree()
{
	verifyf(IsValid(AIAbilityComponent), TEXT("AI Ability Component is invalid."));

	AIAbilityComponent->RunBehaviorTree(BehaviorTree.LoadSynchronous(), TaskName, BuildTask);
}

void UBBBuildAbility::CompleteTask(UIBBAbilityTask * CompletedTask)
{
	verifyf(CompletedTask == BuildTask, TEXT("Completed Task is not the current ability's task."));

	BuildTask->OnTaskCompleted().RemoveAll(this);

	for (int Index = 0; Index < BuildTask->GetNumBuildables(); Index++)
	{
		TScriptInterface<IBBBuildable> Buildable = BuildTask->GetBuildable(Index);

		verifyf(IsValid(Buildable.GetObject()), TEXT("Buildable is invalid."));

		Buildable->RemoveMaterialOverride();
	}

	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}