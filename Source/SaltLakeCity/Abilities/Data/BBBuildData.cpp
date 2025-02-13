// SaltLakeCity 4.26

#include "BBBuildData.h"
#include "Actors/Interfaces/IBBBuildable.h"

UBBBuildData::UBBBuildData() :
	Super()
{
	EventTag = FGameplayTag();
	AbilityTags.Reset();
	TargetingClass = TSoftClassPtr<AIBBTargetingActor>();
	BuildableClasses = TArray<FBBBuildablePtr>();
	Targeting = nullptr;
	Buildables = TArray<TScriptInterface<IBBBuildable>>();
	Price = -1.0f;
	Time = -1.0f;

	EventData = FGameplayEventData();
	EventData.EventTag = EventTag;
	EventData.OptionalObject = this;
}

void UBBBuildData::PostInitProperties()
{
	Super::PostInitProperties();

	Targeting = nullptr;
	Buildables.Empty();
	EventData.EventTag = EventTag;
}

EBBJob UBBBuildData::GetJobType() const
{
	return EBBJob::Builder;
}

FGameplayTag UBBBuildData::GetEventTag() const
{
	return EventTag;
}

FGameplayEventData * UBBBuildData::GetEventData()
{
	return & EventData;
}

FGameplayTagContainer UBBBuildData::GetAbilityTags() const
{
	return AbilityTags;
}

float UBBBuildData::GetPrice() const
{
	return Price;
}

void UBBBuildData::SetPrice(float NewPrice)
{
	Price = NewPrice;
}

float UBBBuildData::GetTime() const
{
	return Time;
}

void UBBBuildData::SetTime(float NewTime)
{
	Time = NewTime;
}

const TSoftClassPtr<AIBBTargetingActor> UBBBuildData::GetTargetingClass() const
{
	return TargetingClass;
}

void UBBBuildData::SetTargetingClass(TSoftClassPtr<AIBBTargetingActor> NewTargetingClass)
{
	TargetingClass = NewTargetingClass;
}

AIBBTargetingActor * UBBBuildData::GetTargetingActor() const
{
	return Targeting;
}

void UBBBuildData::SetTargetingActor(AIBBTargetingActor * NewTargeting)
{
	Targeting = NewTargeting;
}

const TArray<FBBBuildablePtr> UBBBuildData::GetBuildableClasses() const
{
	return BuildableClasses;
}

void UBBBuildData::SetBuildableClasses(const TArray<FBBBuildablePtr> NewBuildableClasses)
{
	BuildableClasses = NewBuildableClasses;
}

int UBBBuildData::AddBuildable(TScriptInterface<IBBBuildable> && Buildable)
{
	return Buildables.Emplace(Buildable);
}

int UBBBuildData::RemoveBuildable(TScriptInterface<IBBBuildable> && Buildable)
{
	return Buildables.Remove(Buildable);
}

int UBBBuildData::GetNumBuildables() const
{
	return Buildables.Num();
}

TScriptInterface<IBBBuildable> UBBBuildData::GetBuildable(int Index) const
{
	return Buildables.IsValidIndex(Index) ? Buildables[Index] : nullptr;
}