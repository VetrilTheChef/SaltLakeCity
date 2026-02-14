// SaltLakeCity 5.7

#include "BBBuildWidgetStub.h"

UBBBuildWidgetStub::UBBBuildWidgetStub(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
	EntriesMap.Empty();
}

void UBBBuildWidgetStub::NativeDestruct()
{
	Super::NativeDestruct();
}

void UBBBuildWidgetStub::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

EBBWidget UBBBuildWidgetStub::GetType() const
{
	return EBBWidget::Build;
}

void UBBBuildWidgetStub::AddToScreen(int32 ZOrder)
{
}

void UBBBuildWidgetStub::AddEntry(EBBBuildCategory Category, UIBBBuildEntry * & NewEntry)
{
	EntriesMap.FindOrAdd(Category).Entries.Emplace(NewEntry);
}

void UBBBuildWidgetStub::ClearEntries(EBBBuildCategory Category)
{
	FBBBuildWidgetStubEntries * CategoryEntries = EntriesMap.Find(Category);

	if (CategoryEntries)
	{
		CategoryEntries->Entries.Empty();
	}
}

int UBBBuildWidgetStub::GetNumEntries(EBBBuildCategory Category)
{
	FBBBuildWidgetStubEntries * CategoryEntries = EntriesMap.Find(Category);

	if (CategoryEntries)
	{
		return CategoryEntries->Entries.Num();
	}

	return 0;
}

UIBBBuildEntry * UBBBuildWidgetStub::GetEntry(EBBBuildCategory Category, int Index)
{
	FBBBuildWidgetStubEntries * CategoryEntries = EntriesMap.Find(Category);

	if (CategoryEntries)
	{
		return CategoryEntries->Entries.IsValidIndex(Index) ? CategoryEntries->Entries[Index] : nullptr;
	}

	return nullptr;
}