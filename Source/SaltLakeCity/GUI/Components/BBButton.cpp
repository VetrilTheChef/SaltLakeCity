// SaltLakeCity 4.26

#include "BBButton.h"
#include "Commands/Interfaces/IBBCommand.h"

UBBButton::UBBButton(const FObjectInitializer & ObjectInitializer) :
	Super(ObjectInitializer)
{
	Command = nullptr;
	ClickDelegate = FScriptDelegate();
}

void UBBButton::PostInitProperties()
{
	Super::PostInitProperties();

	ClickDelegate.BindUFunction(this, TEXT("ExecuteCommand"));

	OnClicked.AddUnique(ClickDelegate);
}

void UBBButton::BeginDestroy()
{
	OnClicked.Remove(ClickDelegate);

	Super::BeginDestroy();
}

void UBBButton::SetCommand(UIBBCommand * NewCommand)
{
	verifyf(IsValid(NewCommand), TEXT("New Command is invalid."));

	Command = NewCommand;
}

void UBBButton::ExecuteCommand()
{
	verifyf(IsValid(Command), TEXT("Command is invalid."));

	Command->Execute();
}