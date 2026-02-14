// SaltLakeCity 4.27

#include "BBDossierEntryModel.h"
#include "GUI/Data/Interfaces/IBBDossierEntry.h"
#include "GUI/Widgets/Interfaces/IBBDossierEntryWidget.h"

UBBDossierEntryModel::UBBDossierEntryModel() :
	Super()
{
	View = nullptr;
	DossierEntry = nullptr;
}

UIBBWidget * UBBDossierEntryModel::GetWidget() const
{
	return View;
}

UIBBWidgetSpecification * UBBDossierEntryModel::GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory)
{
	return nullptr;
}

void UBBDossierEntryModel::Initialize(UIBBDossierEntryWidget * NewView, UIBBDossierEntry * NewDossierEntry)
{
	Finalize();
	InitializeView(NewView);
	InitializeEntry(NewDossierEntry);
}

void UBBDossierEntryModel::Finalize()
{
	FinalizeEntry();
	FinalizeView();
}

FText UBBDossierEntryModel::GetEntryName() const
{
	verifyf(IsValid(DossierEntry), TEXT("Dossier Entry is invalid."));

	return DossierEntry->GetEntryName();
}

TSoftObjectPtr<UTexture2D> UBBDossierEntryModel::GetIcon() const
{
	verifyf(IsValid(DossierEntry), TEXT("Dossier Entry is invalid."));

	return DossierEntry->GetIcon();
}

float UBBDossierEntryModel::GetValue() const
{
	verifyf(IsValid(DossierEntry), TEXT("Dossier Entry is invalid."));

	return DossierEntry->GetValue();
}

float UBBDossierEntryModel::GetMaxValue() const
{
	verifyf(IsValid(DossierEntry), TEXT("Dossier Entry is invalid."));

	return DossierEntry->GetMaxValue();
}



void UBBDossierEntryModel::InitializeView(UIBBDossierEntryWidget * NewView)
{
	FinalizeView();

	verifyf(IsValid(NewView), TEXT("New View is invalid."));

	View = NewView;
}

void UBBDossierEntryModel::InitializeEntry(UIBBDossierEntry * NewDossierEntry)
{
	FinalizeEntry();

	verifyf(IsValid(NewDossierEntry), TEXT("New Dossier Entry is invalid."));

	DossierEntry = NewDossierEntry;

	DossierEntry->OnUpdate().AddUObject(this, & UBBDossierEntryModel::UpdateValues);
}

void UBBDossierEntryModel::FinalizeView()
{
	View = nullptr;
}

void UBBDossierEntryModel::FinalizeEntry()
{
	if (IsValid(DossierEntry))
	{
		DossierEntry->OnUpdate().RemoveAll(this);
	}

	DossierEntry = nullptr;
}

void UBBDossierEntryModel::UpdateValues(float NewValue, float NewMaxValue)
{
	Update.Broadcast(NewValue, NewMaxValue);
}