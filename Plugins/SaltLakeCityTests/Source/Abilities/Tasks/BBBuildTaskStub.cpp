// SaltLakeCity 4.27s

#include "BBBuildTaskStub.h"
#include "Abilities/Data/Interfaces/IBBBuildData.h"

UBBBuildTaskStub::UBBBuildTaskStub() :
	Super()
{
	EventTag = FGameplayTag();
	AbilityTags.Reset();
	BuildData = nullptr;
	EventData = FGameplayEventData();
	Buildables = TArray<TScriptInterface<IBBBuildable>>();
	Progress = -1.0f;
	Price = -1.0f;
	Time = -1.0f;
}

void UBBBuildTaskStub::Decorate(const UIBBAbilityData * NewAbilityData)
{
	BuildData = Cast<UIBBBuildData>(NewAbilityData);
}

EBBJob UBBBuildTaskStub::GetJobType() const
{
	return EBBJob::Builder;
}

FGameplayTag UBBBuildTaskStub::GetEventTag() const
{
	return EventTag;
}

void UBBBuildTaskStub::SetEventTag(FGameplayTag NewEventTag)
{
	EventTag = NewEventTag;
}

FGameplayEventData * UBBBuildTaskStub::GetEventData()
{
	return & EventData;
}

void UBBBuildTaskStub::SetEventData(FGameplayEventData NewEventData)
{
	EventData = NewEventData;
}

FGameplayTagContainer UBBBuildTaskStub::GetAbilityTags() const
{
	return AbilityTags;
}

void UBBBuildTaskStub::SetAbilityTags(FGameplayTagContainer NewAbilityTags)
{
	AbilityTags = NewAbilityTags;
}

float UBBBuildTaskStub::GetProgress() const
{
	return Progress;
}

void UBBBuildTaskStub::SetProgress(float NewProgress)
{
	Progress = NewProgress;
}

float UBBBuildTaskStub::GetPrice() const
{
	return Price;
}

void UBBBuildTaskStub::SetPrice(float NewPrice)
{
	Price = NewPrice;
}

float UBBBuildTaskStub::GetTime() const
{
	return Time;
}

void UBBBuildTaskStub::SetTime(float NewTime)
{
	Time = NewTime;
}

int UBBBuildTaskStub::GetNumBuildables() const
{
	return Buildables.Num();
}

TScriptInterface<IBBBuildable> UBBBuildTaskStub::GetBuildable(int Index) const
{
	return Buildables.IsValidIndex(Index) ? Buildables[Index] : nullptr;
}

void UBBBuildTaskStub::SetBuildables(TArray<TScriptInterface<IBBBuildable>> NewBuildables)
{
	Buildables = NewBuildables;
}


void UBBBuildTaskStub::Complete()
{
	Progress = 1.0f;

	OnTaskCompleted().Broadcast(this);
}