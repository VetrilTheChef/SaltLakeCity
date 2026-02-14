// SaltLakeCity 4.27

#include "BBDossierEntryStub.h"
#include "Actors/Components/Interfaces/IBBAIAbilityComponent.h"
#include "Attributes/Interfaces/IBBBaseAttributeSet.h"

UBBDossierEntryStub::UBBDossierEntryStub() :
	Super()
{
	Name = FText::FromString("");
	Icon = TSoftObjectPtr<UTexture2D>();
	ValueDelegate = FBBGetAttributeDelegate();
	MaxValueDelegate = FBBGetAttributeDelegate();
	AttributeUpdate = nullptr;
	Value = -1.0f;
	MaxValue = -1.0f;
}

void UBBDossierEntryStub::Initialize(FText NewName, TSoftObjectPtr<UTexture2D> NewIcon, FBBGetAttributeDelegate NewValueDelegate, FBBGetAttributeDelegate NewMaxValueDelegate, FBBAttributeUpdate * NewAttributeUpdate)
{
	Name = NewName;
	Icon = NewIcon;
	ValueDelegate = NewValueDelegate;
	MaxValueDelegate = NewMaxValueDelegate;
	AttributeUpdate = NewAttributeUpdate;

	if (AttributeUpdate)
	{
		AttributeUpdate->AddUObject(this, & UBBDossierEntryStub::UpdateEntry);
	}
}

void UBBDossierEntryStub::Finalize()
{
	Name = FText::FromString("");
	Icon = TSoftObjectPtr<UTexture2D>();

	ValueDelegate = FBBGetAttributeDelegate();
	MaxValueDelegate = FBBGetAttributeDelegate();

	if (AttributeUpdate)
	{
		AttributeUpdate->RemoveAll(this);
	}

	AttributeUpdate = nullptr;

	Value = -1.0f;
	MaxValue = -1.0f;
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

	Update.Broadcast(Value, MaxValue);
}

float UBBDossierEntryStub::GetMaxValue() const
{
	return MaxValue;
}

void UBBDossierEntryStub::SetMaxValue(float NewMaxValue)
{
	MaxValue = NewMaxValue;

	Update.Broadcast(Value, MaxValue);
}



void UBBDossierEntryStub::UpdateEntry(float NewValue, float NewMaxValue)
{
	Value = NewValue;

	MaxValue = NewMaxValue;

	Update.Broadcast(Value, MaxValue);
}