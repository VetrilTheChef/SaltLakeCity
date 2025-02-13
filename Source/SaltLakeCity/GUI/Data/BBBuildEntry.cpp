// SaltLakeCity 4.25

#include "BBBuildEntry.h"

UBBBuildEntry::UBBBuildEntry() :
	Super()
{
	Name = FText::FromString("");
	Price = -1.0f;
	Time = -1.0f;
	Buildables.Empty();
}

const FText UBBBuildEntry::GetEntryName() const
{
	return Name;
}

void UBBBuildEntry::SetEntryName(const FText NewName)
{
	Name = NewName;
}

const TSoftObjectPtr<UTexture2D> UBBBuildEntry::GetEntryIcon() const
{
	return Icon;
}

void UBBBuildEntry::SetEntryIcon(const TSoftObjectPtr<UTexture2D> NewIcon)
{
	Icon = NewIcon;
}

const float UBBBuildEntry::GetEntryPrice() const
{
	return Price;
}

void UBBBuildEntry::SetEntryPrice(const float NewPrice)
{
	Price = NewPrice;
}

const float UBBBuildEntry::GetEntryTime() const
{
	return Time;
}

void UBBBuildEntry::SetEntryTime(const float NewTime)
{
	Time = NewTime;
}

const TArray<FBBBuildablePtr> UBBBuildEntry::GetEntryBuildables() const
{
	return Buildables;
}

void UBBBuildEntry::SetEntryBuildables(const TArray<FBBBuildablePtr> NewBuildables)
{
	Buildables = NewBuildables;
}

const TSoftClassPtr<UIBBBuildData> UBBBuildEntry::GetEntryBuildDataClass() const
{
	return BuildDataClass;
}

void UBBBuildEntry::SetEntryBuildDataClass(const TSoftClassPtr<UIBBBuildData> NewBuildDataClass)
{
	BuildDataClass = NewBuildDataClass;
}