// SaltLakeCity 4.26

#include "BBRadioBoxAccessor.h"

UBBRadioBoxAccessor::UBBRadioBoxAccessor(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
	RadioBox = nullptr;
}

void UBBRadioBoxAccessor::Decorate(UIBBRadioBox * NewRadioBox)
{
	RadioBox = NewRadioBox;
}

void UBBRadioBoxAccessor::Initialize(int NewIndex)
{
	if (IsValid(RadioBox))
	{
		RadioBox->Initialize(NewIndex);
	}
}

void UBBRadioBoxAccessor::SetCommand(UIBBCommand * NewCommand)
{
	if (IsValid(RadioBox))
	{
		RadioBox->SetCommand(NewCommand);
	}
}

void UBBRadioBoxAccessor::Finalize()
{
	if (IsValid(RadioBox))
	{
		RadioBox->Finalize();
	}
}

void UBBRadioBoxAccessor::RebuildWidgetPublic()
{
	if (IsValid(RadioBox))
	{
		((UBBRadioBoxAccessor *)RadioBox)->RebuildWidget();
	}
}

void UBBRadioBoxAccessor::BroadcastOnCheckStateChanged(bool bIsChecked)
{
	if (IsValid(RadioBox))
	{
		RadioBox->OnCheckStateChanged.Broadcast(bIsChecked);

		((UBBRadioBoxAccessor *)RadioBox)->RebuildWidget();
	}
}