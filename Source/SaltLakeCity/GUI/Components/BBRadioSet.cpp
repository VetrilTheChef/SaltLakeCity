// SaltLakeCity 5.7

#include "BBRadioSet.h"
#include "Blueprint/WidgetTree.h"
#include "Commands/Interfaces/IBBCommand.h"
#include "Components/CheckBox.h"

UBBRadioSet::UBBRadioSet(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
	Elements.Empty();
}

void UBBRadioSet::NativeConstruct()
{
	Super::NativeConstruct();

	ClearElements();
}

void UBBRadioSet::NativeDestruct()
{
	ClearElements();

	Super::NativeDestruct();
}

void UBBRadioSet::AddElement(UIBBCommand * NewElementCommand)
{
	UCheckBox * NewElement = WidgetTree->ConstructWidget<UCheckBox>(ElementClass.LoadSynchronous());//CreateWidget<UCheckBox>(this, ElementClass.LoadSynchronous());

	verifyf(IsValid(NewElement), TEXT("New Element is invalid"));

	NewElement->OnCheckStateChanged.AddDynamic(this, &UBBRadioSet::ChangeElementState);

	Elements.Emplace(FBBRadioSetElement(NewElement, NewElementCommand));
}

void UBBRadioSet::ClearElements()
{
	for (FBBRadioSetElement & Element : Elements)
	{
		if (IsValid(Element.CheckBox))
		{
			Element.CheckBox->OnCheckStateChanged.RemoveAll(this);

			Element.CheckBox->MarkAsGarbage();
		}

		if (IsValid(Element.Command))
		{
			Element.Command->MarkAsGarbage();
		}

		Element.CheckBox = nullptr;
		Element.Command = nullptr;
	}
}

int UBBRadioSet::GetNumElements()
{
	return Elements.Num();
}



void UBBRadioSet::ChangeElementState(bool bIsChecked)
{
	if (!bIsChecked) return;
}