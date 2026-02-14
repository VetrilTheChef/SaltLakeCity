// SaltLakeCity 5.7

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

	Model->OnUpdate().AddUObject(this, & UBBDossierEntryController::Update);
}

void UBBDossierEntryController::FinalizeModel()
{
	if (IsValid(Model))
	{
		Model->OnUpdate().RemoveAll(this);
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

	float Value = DossierEntryModel.GetValue();
	float MaxValue = DossierEntryModel.GetMaxValue();

	View->SetValue(FText::AsNumber(FMath::FloorToInt(Value)));
	View->SetProgress(Value / MaxValue);
}

void UBBDossierEntryController::FinalizeView()
{
	if (IsValid(View))
	{
		View->MarkAsGarbage();
	}

	View = nullptr;
}

void UBBDossierEntryController::Update(float NewValue, float NewMaxValue)
{
	verifyf(IsValid(View), TEXT("Dossier Entry View is invalid."));

	View->SetValue(FText::AsNumber(FMath::FloorToInt(NewValue)));
	View->SetProgress(NewValue / NewMaxValue);
}