// SaltLakeCity 5.7

#include "BBDossierEntryWidgetStub.h"

UBBDossierEntryWidgetStub::UBBDossierEntryWidgetStub(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	Name = FText::FromString("");
	Icon = nullptr;
	Value = FText::FromString("");
	Progress = -1.0f;
}

EBBWidget UBBDossierEntryWidgetStub::GetType() const
{
	return EBBWidget::DossierEntry;
}

void UBBDossierEntryWidgetStub::AddToScreen(int32 ZOrder)
{
}

FText UBBDossierEntryWidgetStub::GetEntryName() const
{
	return Name;
}

void UBBDossierEntryWidgetStub::SetEntryName(FText NewName)
{
	Name = NewName;
}

UTexture2D* UBBDossierEntryWidgetStub::GetIcon() const
{
	return Icon.Get();
}

void UBBDossierEntryWidgetStub::SetIcon(UTexture2D* NewIcon)
{
	Icon = NewIcon;
}

FText UBBDossierEntryWidgetStub::GetValue() const
{
	return Value;
}

void UBBDossierEntryWidgetStub::SetValue(FText NewValue)
{
	Value = NewValue;
}

float UBBDossierEntryWidgetStub::GetProgress() const
{
	return Progress;
}

void UBBDossierEntryWidgetStub::SetProgress(float NewProgress)
{
	Progress = NewProgress;
}



void UBBDossierEntryWidgetStub::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	Super::NativeOnListItemObjectSet(ListItemObject);
}
