// SaltLakeCity 4.26

#include "BBBuildModel.h"
#include "GUI/Data/BBBuildEntry.h"
#include "GUI/Widgets/Interfaces/IBBBuildWidget.h"
#include "Specifications/GUI/Interfaces/IBBBuildWidgetSpecification.h"
#include "Specifications/GUI/Factories/Interfaces/IBBWidgetSpecificationFactory.h"

UBBBuildModel::UBBBuildModel() :
	Super()
{
	View = nullptr;
	EntriesMap.Empty();
}

void UBBBuildModel::PostInitProperties()
{
	Super::PostInitProperties();
}

UIBBWidget * UBBBuildModel::GetWidget() const
{
	return View;
}

UIBBWidgetSpecification * UBBBuildModel::GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory)
{
	verifyf(IsValid(WidgetSpecificationFactory), TEXT("Widget Specification Factory is invalid."));

	UIBBWidgetSpecification * BuildWidgetSpecification = nullptr;

	WidgetSpecificationFactory->NewBuildWidgetSpecification(BuildWidgetSpecification, this);

	return BuildWidgetSpecification;
}

UDataTable * UBBBuildModel::GetDataTable()
{
	return TableAsset.LoadSynchronous();
}

TSoftClassPtr<UIBBBuildEntry> UBBBuildModel::GetEntryClass()
{
	return BuildEntryClass;
}

void UBBBuildModel::Initialize(UIBBBuildWidget * NewView, UDataTable * Table, TSoftClassPtr<UIBBBuildEntry> NewBuildEntryClass)
{
	InitializeEntries(Table, NewBuildEntryClass);
	InitializeView(NewView);
}

int UBBBuildModel::GetNumEntries(EBBBuildCategory Category)
{
	FBBBuildModelEntries * CategoryEntries = EntriesMap.Find(Category);

	if (CategoryEntries)
	{
		return CategoryEntries->Entries.Num();
	}

	return 0;
}

UIBBBuildEntry * UBBBuildModel::GetEntry(EBBBuildCategory Category, int Index)
{
	FBBBuildModelEntries * CategoryEntries = EntriesMap.Find(Category);

	if (CategoryEntries)
	{
		return CategoryEntries->Entries.IsValidIndex(Index) ? CategoryEntries->Entries[Index] : nullptr;
	}

	return nullptr;
}



void UBBBuildModel::InitializeEntries(UDataTable * Table, TSoftClassPtr<UIBBBuildEntry> NewBuildEntryClass)
{
	FinalizeEntries();

	verifyf(IsValid(Table), TEXT("Build Data Table is invalid."));
	verifyf(!BuildEntryClass.IsNull(), TEXT("Build Entry Class is invalid."));

	for (const TPair<FName, uint8 *> & Iterator : Table->GetRowMap())
	{
		FBBBuildRow * TableRow = (FBBBuildRow *)Iterator.Value;

		if (TableRow)
		{
			UIBBBuildEntry * BuildEntry = NewObject<UIBBBuildEntry>(this, BuildEntryClass.LoadSynchronous());

			verifyf(IsValid(BuildEntry), TEXT("Build Entry is invalid."));

			BuildEntry->SetEntryName(TableRow->Name);
			BuildEntry->SetEntryIcon(TableRow->Icon);
			BuildEntry->SetEntryPrice(TableRow->Price);
			BuildEntry->SetEntryTime(TableRow->Time);
			BuildEntry->SetEntryBuildables(TableRow->GetBuildables());

			EntriesMap.FindOrAdd(TableRow->Category).Entries.Emplace(BuildEntry);
		}
	}
}

void UBBBuildModel::InitializeView(UIBBBuildWidget * NewView)
{
	FinalizeView();

	verifyf(IsValid(NewView), TEXT("New Build View is invalid."));

	View = NewView;
}

void UBBBuildModel::FinalizeEntries()
{
	EntriesMap.Empty();
}

void UBBBuildModel::FinalizeView()
{
	if (IsValid(View))
	{
	}

	View = nullptr;
}

void UBBBuildModel::Finalize()
{
	FinalizeView();
	FinalizeEntries();
}