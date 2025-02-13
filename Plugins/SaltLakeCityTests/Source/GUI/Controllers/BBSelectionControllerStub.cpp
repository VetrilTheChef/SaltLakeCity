// SaltLakeCity 4.26

#include "BBSelectionControllerStub.h"
#include "GUI/Models/Interfaces/IBBSelectionModel.h"
#include "GUI/Widgets/Interfaces/IBBSelectionWidget.h"

UBBSelectionControllerStub::UBBSelectionControllerStub() :
	Super()
{
	View = nullptr;
	Model = nullptr;
}

void UBBSelectionControllerStub::Initialize(UIBBSelectionWidget * SelectionView, UIBBSelectionModel * SelectionModel)
{
	InitializeView(SelectionView);
	InitializeModel(SelectionModel);
}

void UBBSelectionControllerStub::Finalize()
{
	FinalizeModel();
	FinalizeView();
}



void UBBSelectionControllerStub::InitializeView(UIBBSelectionWidget * SelectionView)
{
	View = SelectionView;
}

void UBBSelectionControllerStub::FinalizeView()
{
	if (IsValid(View))
	{
	}

	View = nullptr;
}

void UBBSelectionControllerStub::InitializeModel(UIBBSelectionModel * SelectionModel)
{
	Model = SelectionModel;
}

void UBBSelectionControllerStub::FinalizeModel()
{
	if (IsValid(Model))
	{
	}

	Model = nullptr;
}