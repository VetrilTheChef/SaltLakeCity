// SaltLakeCity 4.26

#include "BBBuildDataStub.h"
#include "Actors/Interfaces/IBBBuildable.h"

UBBBuildDataStub::UBBBuildDataStub() :
	Super()
{
	EventTag = FGameplayTag();
	EventData = FGameplayEventData();
	AbilityTags.Reset();
	BuildDataClass = TSoftClassPtr<UIBBBuildData>();
	TargetingClass = TSoftClassPtr<AIBBTargetingActor>();
	BuildableClasses = TArray<FBBBuildablePtr>();
	Targeting = nullptr;
	Buildables = TArray<TScriptInterface<IBBBuildable>>();
	Price = -1.0f;
	Time = -1.0f;
}

EBBJob UBBBuildDataStub::GetJobType() const
{
	return EBBJob::Builder;
}

FGameplayTag UBBBuildDataStub::GetEventTag() const
{
	return EventTag;
}

void UBBBuildDataStub::SetEventTag(FGameplayTag NewEventTag)
{
	EventTag = NewEventTag;
}

FGameplayEventData * UBBBuildDataStub::GetEventData()
{
	return & EventData;
}

void UBBBuildDataStub::SetEventData(FGameplayEventData NewEventData)
{
	EventData = NewEventData;
}

FGameplayTagContainer UBBBuildDataStub::GetAbilityTags() const
{
	return AbilityTags;
}

void UBBBuildDataStub::SetAbilityTags(FGameplayTagContainer NewAbilityTags)
{
	AbilityTags = NewAbilityTags;
}

float UBBBuildDataStub::GetPrice() const
{
	return Price;
}

void UBBBuildDataStub::SetPrice(float NewPrice)
{
	Price = NewPrice;
}

float UBBBuildDataStub::GetTime() const
{
	return Time;
}

void UBBBuildDataStub::SetTime(float NewTime)
{
	Time = NewTime;
}

const TSoftClassPtr<AIBBTargetingActor> UBBBuildDataStub::GetTargetingClass() const
{
	return TargetingClass;
}

void UBBBuildDataStub::SetTargetingClass(TSoftClassPtr<AIBBTargetingActor> NewTargetingClass)
{
	TargetingClass = NewTargetingClass;
}

AIBBTargetingActor * UBBBuildDataStub::GetTargetingActor() const
{
	return Targeting;
}

void UBBBuildDataStub::SetTargetingActor(AIBBTargetingActor * NewTargeting)
{
	Targeting = NewTargeting;
}

const TArray<FBBBuildablePtr> UBBBuildDataStub::GetBuildableClasses() const
{
	return BuildableClasses;
}

void UBBBuildDataStub::SetBuildableClasses(TArray<FBBBuildablePtr> NewBuildableClasses)
{
	BuildableClasses = NewBuildableClasses;
}

int UBBBuildDataStub::GetNumBuildables() const
{
	return Buildables.Num();
}

int UBBBuildDataStub::AddBuildable(TScriptInterface<IBBBuildable> && Buildable)
{
	return Buildables.Emplace(Buildable);
}

int UBBBuildDataStub::RemoveBuildable(TScriptInterface<IBBBuildable> && Buildable)
{
	return Buildables.Remove(Buildable);
}

TScriptInterface<IBBBuildable> UBBBuildDataStub::GetBuildable(int Index) const
{
	return Buildables.IsValidIndex(Index) ? Buildables[Index] : nullptr;
}

void UBBBuildDataStub::SetBuildables(TArray<TScriptInterface<IBBBuildable>> NewBuildables)
{
	Buildables = NewBuildables;
}

TSoftClassPtr<UIBBBuildData> UBBBuildDataStub::GetBuildDataClass()
{
	return BuildDataClass;
}

void UBBBuildDataStub::SetBuildDataClass(TSoftClassPtr<UIBBBuildData> NewBuildDataClass)
{
	BuildDataClass = NewBuildDataClass;
}
