// SaltLakeCity 4.24

#include "BBCompositeCommand.h"

UBBCompositeCommand::UBBCompositeCommand() :
	Super()
{
	Commands.Empty();
}

int UBBCompositeCommand::Add(UIBBCommand * Command)
{
	return Commands.Emplace(Command);
}

int UBBCompositeCommand::Remove(UIBBCommand * Command)
{
	return Commands.Remove(Command);
}

void UBBCompositeCommand::Empty()
{
	Commands.Empty();
}

void UBBCompositeCommand::Execute()
{
	for (auto& Command : Commands)
	{
		verifyf(IsValid(Command), TEXT("Composited Command is invalid."));
		
		Command->Execute();
	}
}