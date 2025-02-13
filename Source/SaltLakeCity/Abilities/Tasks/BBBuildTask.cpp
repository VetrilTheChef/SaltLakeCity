// SaltLakeCity 4.27

#include "BBBuildTask.h"
#include "Abilities/Data/Interfaces/IBBBuildData.h"
#include "Actors/Buildings/Interfaces/IBBBuilding.h"

UBBBuildTask::UBBBuildTask() :
	Super()
{
	EventTag = FGameplayTag();
	AbilityTags.Reset();
	BuildData = nullptr;

	EventData = FGameplayEventData();
	EventData.EventTag = EventTag;
	EventData.OptionalObject = this;
}

void UBBBuildTask::PostInitProperties()
{
	Super::PostInitProperties();

	EventData.EventTag = EventTag;
}

void UBBBuildTask::Decorate(const UIBBAbilityData * NewAbilityData)
{
	BuildData = Cast<UIBBBuildData>(NewAbilityData);

	verifyf(IsValid(BuildData), TEXT("Build Data is invalid."));
}

const UIBBAbilityData * UBBBuildTask::GetAbilityData() const
{
	return BuildData;
}

EBBJob UBBBuildTask::GetJobType() const
{
	return EBBJob::Builder;
}

FGameplayTag UBBBuildTask::GetEventTag() const
{
	return EventTag;
}

FGameplayEventData * UBBBuildTask::GetEventData()
{
	return & EventData;
}

FGameplayTagContainer UBBBuildTask::GetAbilityTags() const
{
	return AbilityTags;
}

float UBBBuildTask::GetProgress() const
{
	return Progress;
}

void UBBBuildTask::SetProgress(float NewProgress)
{
	Progress = FMath::Clamp(NewProgress, 0.0f, 1.0f);

	if (Progress >= 1.0f)
	{
		CompleteTask();
	}
}

float UBBBuildTask::GetPrice() const
{
	verifyf(IsValid(BuildData), TEXT("Build Data is invalid."));

	return BuildData->GetPrice();
}

float UBBBuildTask::GetTime() const
{
	verifyf(IsValid(BuildData), TEXT("Build Data is invalid."));

	return BuildData->GetTime();
}

int UBBBuildTask::GetNumBuildables() const
{
	verifyf(IsValid(BuildData), TEXT("Build Data is invalid."));

	return BuildData->GetNumBuildables();
}

TScriptInterface<IBBBuildable> UBBBuildTask::GetBuildable(int Index) const
{
	verifyf(IsValid(BuildData), TEXT("Build Data is invalid."));

	return BuildData->GetBuildable(Index);
}

bool UBBBuildTask::operator==(const UIBBAbilityData * Other) const
{
	return BuildData == Other;
}


void UBBBuildTask::CompleteTask()
{
	OnTaskCompleted().Broadcast(this);
}