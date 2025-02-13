// SaltLakeCity 4.27

#include "BBBuildAbilityStub.h"
#include "Abilities/Tasks/Interfaces/IBBBuildTask.h"
#include "Actors/Interfaces/IBBBuildable.h"

UBBBuildAbilityStub::UBBBuildAbilityStub() :
	Super()
{
	TaskName = FName("");
	BuildTask = nullptr;

	CompleteTaskCalls = 0;
}

const FName UBBBuildAbilityStub::GetTaskName() const
{
	return TaskName;
}

const UIBBAbilityTask * UBBBuildAbilityStub::GetTask() const
{
	return BuildTask;
}

const UBehaviorTree * UBBBuildAbilityStub::GetBehaviorTree() const
{
	return nullptr;
}

int UBBBuildAbilityStub::GetNumCompleteTasks() const
{
	return CompleteTaskCalls;
}



void UBBBuildAbilityStub::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData * TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	BuildTask = const_cast<UIBBBuildTask *>(Cast<UIBBBuildTask>(TriggerEventData->OptionalObject));

	if (IsValid(BuildTask))
	{
		BuildTask->OnTaskCompleted().AddUObject(this, & UBBBuildAbilityStub::CompleteTask);
	}
}

void UBBBuildAbilityStub::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UBBBuildAbilityStub::CompleteTask(UIBBAbilityTask * CompletedTask)
{
	CompleteTaskCalls++;

	if (IsValid(BuildTask))
	{
		BuildTask->OnTaskCompleted().RemoveAll(this);
	}

	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}