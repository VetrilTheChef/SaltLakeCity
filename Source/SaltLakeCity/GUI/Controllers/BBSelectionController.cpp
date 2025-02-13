// SaltLakeCity 4.26

#include "BBSelectionController.h"
#include "GUI/Models/Interfaces/IBBSelectionModel.h"
#include "GUI/Widgets/Interfaces/IBBSelectionWidget.h"

UBBSelectionController::UBBSelectionController() :
	Super()
{
	Model = nullptr;
	View = nullptr;
}

void UBBSelectionController::Initialize(UIBBSelectionWidget * SelectionView, UIBBSelectionModel * SelectionModel)
{
	InitializeModel(SelectionModel);
	InitializeView(SelectionView);
}

void UBBSelectionController::Finalize()
{
	FinalizeModel();
	FinalizeView();
}



void UBBSelectionController::InitializeModel(UIBBSelectionModel * SelectionModel)
{
	verifyf(IsValid(SelectionModel), TEXT("Selection Model is invalid."));

	FinalizeModel();

	Model = SelectionModel;
}

void UBBSelectionController::FinalizeModel()
{
	if (IsValid(Model))
	{
	}

	Model = nullptr;
}

void UBBSelectionController::InitializeView(UIBBSelectionWidget * SelectionView)
{
	FinalizeView();

	View = SelectionView;

	verifyf(IsValid(View), TEXT("Selection View is invalid."));
}

void UBBSelectionController::FinalizeView()
{
	if (IsValid(View))
	{
		View->MarkPendingKill();
	}

	View = nullptr;
}