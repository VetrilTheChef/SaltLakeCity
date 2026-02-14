// SaltLakeCity 4.27

#include "BBDossierEntry.h"
#include "Attributes/Interfaces/IBBBaseAttributeSet.h"

UBBDossierEntry::UBBDossierEntry() :
	Super()
{
	Name = FText::FromString("");
	Icon = TSoftObjectPtr<UTexture2D>();
	ValueDelegate = FBBGetAttributeDelegate();
	MaxValueDelegate = FBBGetAttributeDelegate();
	AttributeUpdate = nullptr;
}

void UBBDossierEntry::Initialize(FText NewName, TSoftObjectPtr<UTexture2D> NewIcon, FBBGetAttributeDelegate NewValueDelegate, FBBGetAttributeDelegate NewMaxValueDelegate, FBBAttributeUpdate * NewAttributeUpdate)
{
	Finalize();

	Name = NewName;
	Icon = NewIcon;

	verifyf(NewValueDelegate.IsBound(), TEXT("New Value Delegate is unbound."));

	ValueDelegate = NewValueDelegate;

	verifyf(NewMaxValueDelegate.IsBound(), TEXT("New Max Value Delegate is unbound."));

	MaxValueDelegate = NewMaxValueDelegate;

	verifyf(NewAttributeUpdate, TEXT("New Attribute Update is null."));

	AttributeUpdate = NewAttributeUpdate;

	AttributeUpdate->AddUObject(this, & UBBDossierEntry::UpdateEntry);
}

void UBBDossierEntry::Finalize()
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
}

FText UBBDossierEntry::GetEntryName() const
{
	return Name;
}

TSoftObjectPtr<UTexture2D> UBBDossierEntry::GetIcon() const
{
	return Icon;
}

float UBBDossierEntry::GetValue() const
{
	return ValueDelegate.IsBound() ? ValueDelegate.Execute() : -1.0f;
}

float UBBDossierEntry::GetMaxValue() const
{
	return MaxValueDelegate.IsBound() ? MaxValueDelegate.Execute() : -1.0f;
}



void UBBDossierEntry::UpdateEntry(float NewValue, float NewMaxValue) const
{
	Update.Broadcast(NewValue, NewMaxValue);
}