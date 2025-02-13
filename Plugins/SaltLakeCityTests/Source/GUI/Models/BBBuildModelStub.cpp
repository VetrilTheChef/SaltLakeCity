// SaltLakeCity 4.26

#include "BBBuildModelStub.h"
#include "GUI/Data/BBBuildEntryStub.h"
#include "GUI/Data/Interfaces/IBBBuildEntry.h"
#include "GUI/Widgets/Interfaces/IBBBuildWidget.h"

UBBBuildModelStub::UBBBuildModelStub() :
	Super()
{
	View = nullptr;
	EntriesMap.Empty();
}

void UBBBuildModelStub::PostInitProperties()
{
	Super::PostInitProperties();
}

UIBBWidget * UBBBuildModelStub::GetWidget() const
{
	return View;
}

UDataTable * UBBBuildModelStub::GetDataTable()
{
	return nullptr;
}

TSoftClassPtr<UIBBBuildEntry> UBBBuildModelStub::GetEntryClass()
{
	return nullptr;
}

void UBBBuildModelStub::Initialize(UIBBBuildWidget * NewView, UDataTable * Table, TSoftClassPtr<UIBBBuildEntry> NewBuildEntryClass)
{
	View = NewView;
}

void UBBBuildModelStub::Finalize()
{
}

int UBBBuildModelStub::GetNumEntries(EBBBuildCategory Category)
{
	FBBBuildModelStubEntries * CategoryEntries = EntriesMap.Find(Category);

	if (CategoryEntries)
	{
		return CategoryEntries->Entries.Num();
	}

	return -1;
}

int UBBBuildModelStub::AddEntry(EBBBuildCategory Category, FText NewName, TSoftObjectPtr<UTexture2D> NewIcon, float NewPrice, float NewTime, TArray<FBBBuildablePtr> NewBuildables)
{
	UBBBuildEntryStub * NewEntry = NewObject<UBBBuildEntryStub>(this, UBBBuildEntryStub::StaticClass());

	if (IsValid(NewEntry))
	{
		NewEntry->SetEntryName(NewName);
		NewEntry->SetEntryIcon(NewIcon);
		NewEntry->SetEntryPrice(NewPrice);
		NewEntry->SetEntryTime(NewTime);
		NewEntry->SetEntryCategory(Category);
		NewEntry->SetEntryBuildables(NewBuildables);

		return EntriesMap.FindOrAdd(Category).Entries.Emplace(NewEntry);
	}

	return -1;
}

UIBBBuildEntry * UBBBuildModelStub::GetEntry(EBBBuildCategory Category, int Index)
{
	FBBBuildModelStubEntries * CategoryEntries = EntriesMap.Find(Category);

	if (CategoryEntries)
	{
		return CategoryEntries->Entries.IsValidIndex(Index) ? CategoryEntries->Entries[Index] : nullptr;
	}

	return nullptr;
}