// SaltLakeCity 4.27

#include "BBDossierEntryControllerStub.h"
#include "GUI/Models/Interfaces/IBBDossierEntryModel.h"
#include "GUI/Widgets/Interfaces/IBBDossierEntryWidget.h"

UBBDossierEntryControllerStub::UBBDossierEntryControllerStub() :
	Super()
{
	Model = nullptr;
	View = nullptr;
	ValueText = FText::FromString("");
	Value = -1.0f;
	MaxValue = -1.0f;
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

float UBBDossierEntryControllerStub::GetValue() const
{
	return Value;
}

float UBBDossierEntryControllerStub::GetMaxValue() const
{
	return MaxValue;
}



void UBBDossierEntryControllerStub::InitializeModel(UIBBDossierEntryModel * DossierEntryModel)
{
	FinalizeModel();

	Model = DossierEntryModel;

	if (IsValid(Model))
	{
		Model->OnUpdate().AddUObject(this, & UBBDossierEntryControllerStub::Update);
	}
}

void UBBDossierEntryControllerStub::FinalizeModel()
{
	if (IsValid(Model))
	{
		Model->OnUpdate().RemoveAll(this);
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
			View->SetValue(FText::AsNumber(FMath::FloorToInt(DossierEntryModel->GetValue())));
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

void UBBDossierEntryControllerStub::Update(float NewValue, float NewMaxValue)
{
	Value = NewValue;

	MaxValue = NewMaxValue;
}
