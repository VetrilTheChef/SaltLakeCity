// SaltLakeCity 4.27

#include "BBDossierEntryControllerStub.h"
#include "GUI/Models/Interfaces/IBBDossierEntryModel.h"
#include "GUI/Widgets/Interfaces/IBBDossierEntryWidget.h"

UBBDossierEntryControllerStub::UBBDossierEntryControllerStub() :
	Super()
{
	Model = nullptr;
	View = nullptr;
}

void UBBDossierEntryControllerStub::Initialize(UIBBDossierEntryWidget * DossierEntryView, UIBBDossierEntryModel * DossierEntryModel)
{
	InitializeModel(DossierEntryModel);
	InitializeView(DossierEntryView, DossierEntryModel);
}

void UBBDossierEntryControllerStub::Finalize()
{
	FinalizeModel();
	FinalizeView();
}


void UBBDossierEntryControllerStub::InitializeModel(UIBBDossierEntryModel * DossierEntryModel)
{
	FinalizeModel();

	Model = DossierEntryModel;
}

void UBBDossierEntryControllerStub::FinalizeModel()
{
	if (IsValid(Model))
	{
	}

	Model = nullptr;
}

void UBBDossierEntryControllerStub::InitializeView(UIBBDossierEntryWidget * DossierEntryView, UIBBDossierEntryModel * DossierEntryModel)
{
	FinalizeView();

	View = DossierEntryView;

	if (IsValid(View))
	{
		if (IsValid(DossierEntryModel))
		{
			View->SetEntryName(DossierEntryModel->GetEntryName());
			View->SetIcon(DossierEntryModel->GetIcon().LoadSynchronous());
			View->SetValue(DossierEntryModel->GetValue());
			View->SetMaxValue(DossierEntryModel->GetMaxValue());
		}
	}
}

void UBBDossierEntryControllerStub::FinalizeView()
{
	if (IsValid(View))
	{
	}

	View = nullptr;
}