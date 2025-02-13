// SaltLakeCity 4.26

#include "BBAbilityDataStub.h"

UBBAbilityDataStub::UBBAbilityDataStub() :
	Super()
{
	EventTag = FGameplayTag();
	EventData = FGameplayEventData();
	AbilityTags.Reset();
}

EBBJob UBBAbilityDataStub::GetJobType() const
{
	return EBBJob::Builder;
}

FGameplayTag UBBAbilityDataStub::GetEventTag() const
{
	return EventTag;
}

void UBBAbilityDataStub::SetEventTag(FGameplayTag NewEventTag)
{
	EventTag = NewEventTag;
}

FGameplayEventData * UBBAbilityDataStub::GetEventData()
{
	return & EventData;
}

void UBBAbilityDataStub::SetEventData(FGameplayEventData NewEventData)
{
	EventData = NewEventData;
}

FGameplayTagContainer UBBAbilityDataStub::GetAbilityTags() const
{
	return AbilityTags;
}

void UBBAbilityDataStub::SetAbilityTags(FGameplayTagContainer NewAbilityTags)
{
	AbilityTags = NewAbilityTags;
}