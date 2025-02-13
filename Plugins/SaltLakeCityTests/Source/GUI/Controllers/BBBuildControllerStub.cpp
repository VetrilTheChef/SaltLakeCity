// SaltLakeCity 4.26

#include "BBBuildControllerStub.h"
#include "GUI/Factories/Interfaces/IBBWidgetFactory.h"
#include "GUI/Models/Interfaces/IBBBuildModel.h"
#include "GUI/Widgets/Interfaces/IBBBuildWidget.h"
#include "GUI/Widgets/Interfaces/IBBTitleWidget.h"

UBBBuildControllerStub::UBBBuildControllerStub() :
	Super()
{
	Model = nullptr;
	View = nullptr;
}

void UBBBuildControllerStub::Initialize(UIBBBuildWidget * BuildView, UIBBBuildModel * BuildModel)
{
	InitializeModel(BuildModel);
	InitializeView(BuildView);
}

void UBBBuildControllerStub::Finalize()
{
	FinalizeModel();
	FinalizeView();
}

void UBBBuildControllerStub::InitializeModel(UIBBBuildModel * BuildModel)
{
	FinalizeModel();

	Model = BuildModel;

	if (IsValid(Model))
	{
	}
}

void UBBBuildControllerStub::FinalizeModel()
{
	if (IsValid(Model))
	{
	}

	Model = nullptr;
}

void UBBBuildControllerStub::InitializeView(UIBBBuildWidget * BuildView)
{
	FinalizeView();

	View = BuildView;

	if (IsValid(View) && IsValid(Model))
	{
		AddEntries(* View, * Model);
	}
}

void UBBBuildControllerStub::FinalizeView()
{
	if (IsValid(View))
	{
		ClearEntries(* View);
	}

	View = nullptr;
}

void UBBBuildControllerStub::AddEntries(UIBBBuildWidget & BuildView, UIBBBuildModel & BuildModel)
{
	ClearEntries(BuildView);

	#define EBBBUILDCATEGORY_OPERATION(Value) AddEntriesOfCategory(Value, BuildView, BuildModel);

		FOREACH_ENUM_EBBBUILDCATEGORY(EBBBUILDCATEGORY_OPERATION)

	#undef EBBBUILDCATEGORY_OPERATION
}

void UBBBuildControllerStub::AddEntriesOfCategory(EBBBuildCategory Category, UIBBBuildWidget & BuildView, UIBBBuildModel & BuildModel)
{
	int Entries = BuildModel.GetNumEntries(Category);

	for (int EntryIndex = 0; EntryIndex < Entries; EntryIndex++)
	{
		UIBBBuildEntry * Entry = BuildModel.GetEntry(Category, EntryIndex);

		BuildView.AddEntry(Category, Entry);
	}
}

void UBBBuildControllerStub::ClearEntries(UIBBBuildWidget & BuildView)
{
	#define EBBBUILDCATEGORY_OPERATION(Value) ClearEntriesOfCategory(Value, BuildView);

		FOREACH_ENUM_EBBBUILDCATEGORY(EBBBUILDCATEGORY_OPERATION)

	#undef EBBBUILDCATEGORY_OPERATION
}

void UBBBuildControllerStub::ClearEntriesOfCategory(EBBBuildCategory Category, UIBBBuildWidget & BuildView)
{
	BuildView.ClearEntries(Category);
}
