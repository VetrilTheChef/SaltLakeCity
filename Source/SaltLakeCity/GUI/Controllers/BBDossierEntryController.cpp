// SaltLakeCity 4.27

#include "BBDossierEntryController.h"
#include "GUI/Models/Interfaces/IBBDossierEntryModel.h"
#include "GUI/Widgets/Interfaces/IBBDossierEntryWidget.h"

UBBDossierEntryController::UBBDossierEntryController() :
	Super()
{
}

void UBBDossierEntryController::Initialize(UIBBDossierEntryWidget * DossierEntryView, UIBBDossierEntryModel * DossierEntryModel)
{
	InitializeModel(DossierEntryModel);
	InitializeView(DossierEntryView, * DossierEntryModel);
}

void UBBDossierEntryController::Finalize()
{
	FinalizeModel();
	FinalizeView();
}



void UBBDossierEntryController::InitializeModel(UIBBDossierEntryModel * DossierEntryModel)
{
	FinalizeModel();

	verifyf(IsValid(DossierEntryModel), TEXT("Dossier Entry Model is invalid."));

	Model = DossierEntryModel;

	Model->OnValueUpdate().AddUObject(this, & UBBDossierEntryController::UpdateValue);
	Model->OnMaxValueUpdate().AddUObject(this, & UBBDossierEntryController::UpdateMaxValue);
}

void UBBDossierEntryController::FinalizeModel()
{
	if (IsValid(Model))
	{
		Model->OnValueUpdate().RemoveAll(this);
		Model->OnMaxValueUpdate().RemoveAll(this);
	}

	Model = nullptr;
}

void UBBDossierEntryController::InitializeView(UIBBDossierEntryWidget * DossierEntryView, UIBBDossierEntryModel & DossierEntryModel)
{
	FinalizeView();

	verifyf(IsValid(DossierEntryView), TEXT("Dossier Entry View is invalid."));

	View = DossierEntryView;

	View->SetEntryName(DossierEntryModel.GetEntryName());
	View->SetIcon(DossierEntryModel.GetIcon().LoadSynchronous());
	View->SetValue(DossierEntryModel.GetValue());
	View->SetMaxValue(DossierEntryModel.GetMaxValue());
}

void UBBDossierEntryController::FinalizeView()
{
	if (IsValid(View))
	{
		View->MarkPendingKill();
	}

	View = nullptr;
}

void UBBDossierEntryController::UpdateValue(float NewValue)
{
	verifyf(IsValid(View), TEXT("Dossier Entry View is invalid."));

	View->SetValue(NewValue);
}

void UBBDossierEntryController::UpdateMaxValue(float NewValue)
{
	verifyf(IsValid(View), TEXT("Dossier Entry View is invalid."));

	View->SetMaxValue(NewValue);
}