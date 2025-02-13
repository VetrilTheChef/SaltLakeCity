// SaltLakeCity 4.27

#include "BBDossierEntryStub.h"
#include "Actors/Components/Interfaces/IBBAIAbilityComponent.h"

UBBDossierEntryStub::UBBDossierEntryStub() :
	Super()
{
	Name = FText::FromString("");
	Icon = TSoftObjectPtr<UTexture2D>();
	AttributeValueUpdate = nullptr;
	MaxAttributeValueUpdate = nullptr;
	Value = -1.0f;
	MaxValue = -1.0f;
}

void UBBDossierEntryStub::Initialize(FText NewName, TSoftObjectPtr<UTexture2D> NewIcon, FBBUpdate * NewAttributeValueUpdate, FBBUpdate * NewMaxAttributeValueUpdate)
{
	Name = FText::FromString("");
	Icon = TSoftObjectPtr<UTexture2D>();
	AttributeValueUpdate = NewAttributeValueUpdate;

	if (AttributeValueUpdate)
	{
		AttributeValueUpdate->AddUObject(this, & UBBDossierEntryStub::UpdateValue);
	}

	MaxAttributeValueUpdate = NewMaxAttributeValueUpdate;

	if (MaxAttributeValueUpdate)
	{
		MaxAttributeValueUpdate->AddUObject(this, & UBBDossierEntryStub::UpdateMaxValue);
	}
}

void UBBDossierEntryStub::Finalize()
{
	Name = FText::FromString("");
	Icon = TSoftObjectPtr<UTexture2D>();

	Value = -1.0f;
	MaxValue = -1.0f;

	if (AttributeValueUpdate)
	{
		AttributeValueUpdate->RemoveAll(this);
	}

	AttributeValueUpdate = nullptr;

	if (MaxAttributeValueUpdate)
	{
		MaxAttributeValueUpdate->RemoveAll(this);
	}

	MaxAttributeValueUpdate = nullptr;
}


FText UBBDossierEntryStub::GetEntryName() const
{
	return Name;
}

void UBBDossierEntryStub::SetEntryName(FText NewName)
{
	Name = NewName;
}

TSoftObjectPtr<UTexture2D> UBBDossierEntryStub::GetIcon() const
{
	return Icon;
}

void UBBDossierEntryStub::SetIcon(TSoftObjectPtr<UTexture2D> NewIcon)
{
	Icon = NewIcon;
}

float UBBDossierEntryStub::GetValue() const
{
	return Value;
}

void UBBDossierEntryStub::SetValue(float NewValue)
{
	Value = NewValue;
}

float UBBDossierEntryStub::GetMaxValue() const
{
	return MaxValue;
}

void UBBDossierEntryStub::SetMaxValue(float NewMaxValue)
{
	MaxValue = NewMaxValue;
}

bool UBBDossierEntryStub::operator==(const UIBBDossierEntry * Other) const
{
	return (IsValid(Other) &&
			Name == Other->GetEntryName() &&
			Icon == Other->GetIcon() &&
			ValueUpdate == Other->ValueUpdate &&
			MaxValueUpdate == Other->MaxValueUpdate &&
			Value == Other->Value &&
			MaxValue == Other->MaxValue);
}


void UBBDossierEntryStub::UpdateValue(float NewValue)
{
	ValueUpdate.Broadcast(NewValue);
}

void UBBDossierEntryStub::UpdateMaxValue(float NewMaxValue)
{
	MaxValueUpdate.Broadcast(NewMaxValue);
}