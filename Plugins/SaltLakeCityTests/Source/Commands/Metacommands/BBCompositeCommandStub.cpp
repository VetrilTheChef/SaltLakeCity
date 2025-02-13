// SaltLakeCity 4.27

#include "BBCompositeCommandStub.h"

UBBCompositeCommandStub::UBBCompositeCommandStub() :
	Super()
{
	Commands.Empty();

	Executions = 0;
}

int UBBCompositeCommandStub::Add(UIBBCommand * Command)
{
	return Commands.Emplace(Command);
}

int UBBCompositeCommandStub::Remove(UIBBCommand * Command)
{
	return Commands.Remove(Command);
}

void UBBCompositeCommandStub::Empty()
{
	Commands.Empty();
}

void UBBCompositeCommandStub::Execute()
{
	for (UIBBCommand * & Command : Commands)
	{
		Command->Execute();
	}

	Executions++;
}

int UBBCompositeCommandStub::GetNumExecutions() const
{
	return Executions;
}