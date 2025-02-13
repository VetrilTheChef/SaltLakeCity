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
	verifyf(IsValid(DossierEntry), TEXT("Attribute Entry is invalid."));

	return DossierEntry->GetEntryName();
}

TSoftObjectPtr<UTexture2D> UBBDossierEntryModel::GetIcon() const
{
	verifyf(IsValid(DossierEntry), TEXT("Attribute Entry is invalid."));

	return DossierEntry->GetIcon();
}

float UBBDossierEntryModel::GetValue() const
{
	verifyf(IsValid(DossierEntry), TEXT("Attribute Entry is invalid."));

	return DossierEntry->GetValue();
}

float UBBDossierEntryModel::GetMaxValue() const
{
	verifyf(IsValid(DossierEntry), TEXT("Attribute Entry is invalid."));

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

	verifyf(IsValid(NewDossierEntry), TEXT("New Attribute Entry is invalid."));

	DossierEntry = NewDossierEntry;

	DossierEntry->OnValueUpdate().AddUObject(this, & UBBDossierEntryModel::UpdateValue);
	DossierEntry->OnMaxValueUpdate().AddUObject(this, & UBBDossierEntryModel::UpdateMaxValue);
}

void UBBDossierEntryModel::FinalizeView()
{
	View = nullptr;
}

void UBBDossierEntryModel::FinalizeEntry()
{
	if (IsValid(DossierEntry))
	{
		DossierEntry->OnValueUpdate().RemoveAll(this);
		DossierEntry->OnMaxValueUpdate().RemoveAll(this);
	}

	DossierEntry = nullptr;
}

void UBBDossierEntryModel::UpdateValue(float NewValue)
{
	float Value = NewValue;

	// Perform any changes as required

	ValueUpdate.Broadcast(Value);
}

void UBBDossierEntryModel::UpdateMaxValue(float NewMaxValue)
{
	float MaxValue = NewMaxValue;

	// Perform any changes as required

	ValueUpdate.Broadcast(MaxValue);
}