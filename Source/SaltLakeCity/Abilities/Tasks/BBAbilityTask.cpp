// SaltLakeCity 4.26

#include "BBAbilityTask.h"
#include "Abilities/Data/Interfaces/IBBAbilityData.h"

UBBAbilityTask::UBBAbilityTask() :
	Super()
{
	EventTag = FGameplayTag();
	AbilityTags.Reset();
	AbilityData = nullptr;

	EventData = FGameplayEventData();
	EventData.EventTag = EventTag;
	EventData.OptionalObject = this;
}

void UBBAbilityTask::Decorate(const UIBBAbilityData * NewAbilityData)
{
	verifyf(IsValid(NewAbilityData), TEXT("New Ability Data is invalid."));

	AbilityData = NewAbilityData;
}

const UIBBAbilityData * UBBAbilityTask::GetAbilityData() const
{
	return AbilityData;
}

EBBJob UBBAbilityTask::GetJobType() const
{
	return Job;
}

FGameplayTag UBBAbilityTask::GetEventTag() const
{
	return EventTag;
}

FGameplayEventData * UBBAbilityTask::GetEventData()
{
	return & EventData;
}

FGameplayTagContainer UBBAbilityTask::GetAbilityTags() const
{
	return AbilityTags;
}

float UBBAbilityTask::GetProgress() const
{
	return Progress;
}

void UBBAbilityTask::SetProgress(float NewProgress)
{
	Progress = FMath::Clamp(NewProgress, 0.0f, 1.0f);

	if (Progress >= 1.0f)
	{
		CompleteTask();
	}
}

bool UBBAbilityTask::operator==(const UIBBAbilityData * Other) const
{
	return AbilityData == Other;
}



void UBBAbilityTask::CompleteTask()
{
	OnTaskCompleted().Broadcast(this);
}