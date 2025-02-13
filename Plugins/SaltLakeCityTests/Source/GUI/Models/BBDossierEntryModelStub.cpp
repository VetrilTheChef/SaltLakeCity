// SaltLakeCity 4.27

#include "BBDossierEntryModelStub.h"
#include "GUI/Widgets/Interfaces/IBBDossierEntryWidget.h"

UBBDossierEntryModelStub::UBBDossierEntryModelStub() :
	Super()
{
	View = nullptr;
	DossierEntry = nullptr;
	Name = FText::FromString("");
	Icon = TSoftObjectPtr<UTexture2D>();
	Value = -1.0f;
	MaxValue = -1.0f;
}

UIBBWidget * UBBDossierEntryModelStub::GetWidget() const
{
	return View;
}

UIBBWidgetSpecification * UBBDossierEntryModelStub::GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory)
{
	return nullptr;
}

void UBBDossierEntryModelStub::Initialize(UIBBDossierEntryWidget * NewView, UIBBDossierEntry * NewDossierEntry)
{
	Finalize();

	View = NewView;
	DossierEntry = NewDossierEntry;
}

void UBBDossierEntryModelStub::Finalize()
{
	View = nullptr;
	DossierEntry = nullptr;
	Name = FText::FromString("");
	Icon = TSoftObjectPtr<UTexture2D>();
	Value = -1.0f;
	MaxValue = -1.0f;
}

FText UBBDossierEntryModelStub::GetEntryName() const
{
	return Name;
}

void UBBDossierEntryModelStub::SetEntryName(FText NewName)
{
	Name = NewName;
}

TSoftObjectPtr<UTexture2D> UBBDossierEntryModelStub::GetIcon() const
{
	return Icon;
}

void UBBDossierEntryModelStub::SetIcon(TSoftObjectPtr<UTexture2D> NewIcon)
{
	Icon = NewIcon;
}

UIBBDossierEntry * UBBDossierEntryModelStub::GetEntry() const
{
	return DossierEntry;
}

void UBBDossierEntryModelStub::SetEntry(UIBBDossierEntry * NewDossierEntry)
{
	DossierEntry = NewDossierEntry;
}

float UBBDossierEntryModelStub::GetValue() const
{
	return Value;
}

void UBBDossierEntryModelStub::SetValue(float NewValue)
{
	Value = NewValue;
}

float UBBDossierEntryModelStub::GetMaxValue() const
{
	return MaxValue;
}

void UBBDossierEntryModelStub::SetMaxValue(float NewMaxValue)
{
	MaxValue = NewMaxValue;
}