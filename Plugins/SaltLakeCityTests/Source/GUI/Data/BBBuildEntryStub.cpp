// SaltLakeCity 4.26

#include "BBBuildEntryStub.h"

UBBBuildEntryStub::UBBBuildEntryStub() :
	Super()
{
	Name = FText::FromString("");
	Price = -1.0f;
	Time = -1.0f;
	Category = EBBBuildCategory::None;
	Buildables.Empty();
	BuildDataClass = nullptr;
}

const FText UBBBuildEntryStub::GetEntryName() const
{
	return Name;
}

void UBBBuildEntryStub::SetEntryName(const FText NewName)
{
	Name = NewName;
}

const TSoftObjectPtr<UTexture2D> UBBBuildEntryStub::GetEntryIcon() const
{
	return Icon;
}

void UBBBuildEntryStub::SetEntryIcon(const TSoftObjectPtr<UTexture2D> NewIcon)
{
	Icon = NewIcon;
}

const float UBBBuildEntryStub::GetEntryPrice() const
{
	return Price;
}

void UBBBuildEntryStub::SetEntryPrice(const float NewPrice)
{
	Price = NewPrice;
}

const float UBBBuildEntryStub::GetEntryTime() const
{
	return Time;
}

void UBBBuildEntryStub::SetEntryTime(const float NewTime)
{
	Time = NewTime;
}

const TArray<FBBBuildablePtr> UBBBuildEntryStub::GetEntryBuildables() const
{
	return Buildables;
}

void UBBBuildEntryStub::SetEntryBuildables(const TArray<FBBBuildablePtr> NewBuildables)
{
	Buildables = NewBuildables;
}

const EBBBuildCategory UBBBuildEntryStub::GetEntryCategory() const
{
	return Category;
}

void UBBBuildEntryStub::SetEntryCategory(const EBBBuildCategory NewCategory)
{
	Category = NewCategory;
}

const TSoftClassPtr<UIBBBuildData> UBBBuildEntryStub::GetEntryBuildDataClass() const
{
	return BuildDataClass;
}

void UBBBuildEntryStub::SetEntryBuildDataClass(const TSoftClassPtr<UIBBBuildData> NewBuildDataClass)
{
	BuildDataClass = NewBuildDataClass;
}