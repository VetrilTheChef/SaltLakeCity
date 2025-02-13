// SaltLakeCity 4.26

#include "BBRadioBox.h"
#include "Commands/Interfaces/IBBCommand.h"

UBBRadioBox::UBBRadioBox(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
	Index = -1;
	Command = nullptr;
}

void UBBRadioBox::Initialize(int NewIndex)
{
	Index = NewIndex;
	
	//OnCheckStateChanged.AddDynamic(this, &UBBRadioBox::ChangeCheckState);
}

void UBBRadioBox::SetCommand(UIBBCommand * NewCommand)
{
	verifyf(IsValid(NewCommand), TEXT("New Command is invalid."));

	Command = NewCommand;
}

void UBBRadioBox::Finalize()
{
	//OnCheckStateChanged.RemoveDynamic(this, &UBBRadioBox::ChangeCheckState);

	Index = -1;

	if (IsValid(Command))
	{
		Command->MarkPendingKill();
	}

	Command = nullptr;
}

TSharedRef<SWidget> UBBRadioBox::RebuildWidget()
{
	return Super::RebuildWidget();
}



void UBBRadioBox::ChangeCheckState(bool bIsChecked)
{
	if (bIsChecked)
	{
		OnRadioStateChanged().Broadcast(Index);

		if (IsValid(Command))
		{
			Command->Execute();
		}
	}
}