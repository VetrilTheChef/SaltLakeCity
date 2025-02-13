// SaltLakeCity 4.27

#include "BBDossierEntry.h"
#include "Attributes/Interfaces/IBBBaseAttributeSet.h"

UBBDossierEntry::UBBDossierEntry() :
	Super()
{
	Name = FText::FromString("");
	Icon = TSoftObjectPtr<UTexture2D>();
	AttributeValueUpdate = nullptr;
	MaxAttributeValueUpdate = nullptr;
}

void UBBDossierEntry::Initialize(FText NewName, TSoftObjectPtr<UTexture2D> NewIcon, UIBBBaseAttributeSet::FBBUpdate * NewAttributeValueUpdate, UIBBBaseAttributeSet::FBBUpdate * NewMaxAttributeValueUpdate)
{
	Finalize();

	Name = NewName;
	Icon = NewIcon;

	verifyf(NewAttributeValueUpdate, TEXT("New Attribute Value Update is null."));
	verifyf(NewMaxAttributeValueUpdate, TEXT("New Max Attribute Value Update is null."));

	AttributeValueUpdate = NewAttributeValueUpdate;
	MaxAttributeValueUpdate = NewMaxAttributeValueUpdate;

	AttributeValueUpdate->AddUObject(this, & UBBDossierEntry::UpdateValue);
	MaxAttributeValueUpdate->AddUObject(this, & UBBDossierEntry::UpdateMaxValue);
}

void UBBDossierEntry::Finalize()
{
	Name = FText::FromString("");
	Icon = TSoftObjectPtr<UTexture2D>();

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

FText UBBDossierEntry::GetEntryName() const
{
	return Name;
}

TSoftObjectPtr<UTexture2D> UBBDossierEntry::GetIcon() const
{
	return Icon;
}



void UBBDossierEntry::UpdateValue(float NewValue) const
{
	ValueUpdate.Broadcast(NewValue);
}

void UBBDossierEntry::UpdateMaxValue(float NewMaxValue) const
{
	MaxValueUpdate.Broadcast(NewMaxValue);
}