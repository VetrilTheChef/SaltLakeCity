// SaltLakeCity 4.27

#include "BBDossierControllerStub.h"
#include "GUI/Models/Interfaces/IBBDossierModel.h"
#include "GUI/Widgets/Interfaces/IBBDossierWidget.h"

UBBDossierControllerStub::UBBDossierControllerStub() :
	Super()
{
	Model = nullptr;
	View = nullptr;

	DisplayName = FText::FromString("");
}

void UBBDossierControllerStub::PostInitProperties()
{
	Super::PostInitProperties();
}

void UBBDossierControllerStub::BeginDestroy()
{
	Super::BeginDestroy();
}

void UBBDossierControllerStub::Initialize(UIBBDossierWidget * DossierView, UIBBDossierModel * DossierModel, const UIBBWidgetFactory * WidgetFactory, const UIBBSpecificationFactory * SpecificationFactory, const UIBBCommandFactory * CommandFactory)
{
	InitializeModel(DossierModel);
	InitializeView(DossierView);
}

void UBBDossierControllerStub::Finalize()
{
	FinalizeView();
	FinalizeModel();
}

FText UBBDossierControllerStub::GetDisplayName()
{
	return DisplayName;
}



void UBBDossierControllerStub::InitializeModel(UIBBDossierModel * DossierModel)
{
	FinalizeModel();

	if (IsValid(DossierModel))
	{
		Model = DossierModel;

		Model->OnDisplayNameUpdate().AddUObject(this, & UBBDossierControllerStub::UpdateDisplayName);
	}
}

void UBBDossierControllerStub::FinalizeModel()
{
	if (IsValid(Model))
	{
		Model->OnDisplayNameUpdate().RemoveAll(this);
	}

	Model = nullptr;
}

void UBBDossierControllerStub::InitializeView(UIBBDossierWidget * DossierView)
{
	FinalizeView();

	if (IsValid(DossierView))
	{
		View = DossierView;
	}
}

void UBBDossierControllerStub::FinalizeView()
{
	View = nullptr;
}

void UBBDossierControllerStub::UpdateDisplayName(FText NewDisplayName)
{
	DisplayName = NewDisplayName;
}