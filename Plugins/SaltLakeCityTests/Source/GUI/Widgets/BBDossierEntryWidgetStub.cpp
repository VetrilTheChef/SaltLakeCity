// SaltLakeCity 4.27

#include "BBDossierEntryWidgetStub.h"

UBBDossierEntryWidgetStub::UBBDossierEntryWidgetStub(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
	Name = FText::FromString("");
	Icon = nullptr;
	Value = -1.0f;
	MaxValue = -1.0f;
}

EBBWidget UBBDossierEntryWidgetStub::GetType() const
{
	return EBBWidget::DossierEntry;
}

FText UBBDossierEntryWidgetStub::GetEntryName() const
{
	return Name;
}

void UBBDossierEntryWidgetStub::SetEntryName(FText NewName)
{
	Name = NewName;
}

UTexture2D * UBBDossierEntryWidgetStub::GetIcon() const
{
	return Icon;
}

void UBBDossierEntryWidgetStub::SetIcon(UTexture2D * NewIcon)
{
	Icon = NewIcon;
}

float UBBDossierEntryWidgetStub::GetValue() const
{
	return Value;
}

void UBBDossierEntryWidgetStub::SetValue(float NewValue)
{
	Value = NewValue;
}

float UBBDossierEntryWidgetStub::GetMaxValue() const
{
	return MaxValue;
}

void UBBDossierEntryWidgetStub::SetMaxValue(float NewMaxValue)
{
	MaxValue = NewMaxValue;
}



void UBBDossierEntryWidgetStub::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	Super::NativeOnListItemObjectSet(ListItemObject);
}
