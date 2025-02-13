// SaltLakeCity 4.26

#include "BBBuildController.h"
#include "GUI/Data/Interfaces/IBBBuildEntry.h"
#include "GUI/Includes/BBBuildCategoryEnum.h"
#include "GUI/Models/Interfaces/IBBBuildModel.h"
#include "GUI/Widgets/Interfaces/IBBBuildWidget.h"
#include "GUI/Widgets/Interfaces/IBBTitleWidget.h"
#include "GUI/Widgets/BBBuildEntryWidget.h"

UBBBuildController::UBBBuildController() :
	Super()
{
	Model = nullptr;
	View = nullptr;
}

void UBBBuildController::Initialize(UIBBBuildWidget * BuildView, UIBBBuildModel * BuildModel)
{
	InitializeModel(BuildModel);
	InitializeView(BuildView);
}

void UBBBuildController::Finalize()
{
	FinalizeModel();
	FinalizeView();
}



void UBBBuildController::InitializeModel(UIBBBuildModel * BuildModel)
{
	FinalizeModel();

	verifyf(IsValid(BuildModel), TEXT("Build Model is invalid."));

	Model = BuildModel;
}

void UBBBuildController::FinalizeModel()
{
	if (IsValid(Model))
	{
	}

	Model = nullptr;
}

void UBBBuildController::InitializeView(UIBBBuildWidget * BuildView)
{
	FinalizeView();

	verifyf(IsValid(BuildView), TEXT("Build View is invalid."));

	View = BuildView;

	AddEntries(* View, * Model);
}

void UBBBuildController::FinalizeView()
{
	if (IsValid(View))
	{
		ClearEntries(* View);
	}

	View = nullptr;
}

void UBBBuildController::AddEntries(UIBBBuildWidget & BuildView, UIBBBuildModel & BuildModel)
{
	ClearEntries(BuildView);

	#define EBBBUILDCATEGORY_OPERATION(Value) AddEntriesOfCategory(Value, BuildView, BuildModel);

		FOREACH_ENUM_EBBBUILDCATEGORY(EBBBUILDCATEGORY_OPERATION)

	#undef EBBBUILDCATEGORY_OPERATION
}

void UBBBuildController::AddEntriesOfCategory(EBBBuildCategory Category, UIBBBuildWidget & BuildView, UIBBBuildModel & BuildModel)
{
	int Entries = BuildModel.GetNumEntries(Category);

	for (int EntryIndex = 0; EntryIndex < Entries; EntryIndex++)
	{
		UIBBBuildEntry * Entry = BuildModel.GetEntry(Category, EntryIndex);

		BuildView.AddEntry(Category, Entry);
	}
}

void UBBBuildController::ClearEntries(UIBBBuildWidget & BuildView)
{
	#define EBBBUILDCATEGORY_OPERATION(Value) ClearEntriesOfCategory(Value, BuildView);

		FOREACH_ENUM_EBBBUILDCATEGORY(EBBBUILDCATEGORY_OPERATION)

	#undef EBBBUILDCATEGORY_OPERATION
}

void UBBBuildController::ClearEntriesOfCategory(EBBBuildCategory Category, UIBBBuildWidget & BuildView)
{
	BuildView.ClearEntries(Category);
}