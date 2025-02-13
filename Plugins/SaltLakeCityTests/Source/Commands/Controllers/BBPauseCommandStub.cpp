// SaltLakeCity 4.27

#include "BBPauseCommandStub.h"

UBBPauseCommandStub::UBBPauseCommandStub() :
	Super()
{
	Controller = nullptr;
	Executions = 0;
}

AIBBPlayerController * UBBPauseCommandStub::GetController()
{
	return Controller;
}

void UBBPauseCommandStub::SetController(AIBBPlayerController * NewController)
{
	Controller = NewController;
}

void UBBPauseCommandStub::Execute()
{
	Executions++;
}

int UBBPauseCommandStub::GetNumExecutions() const
{
	return Executions;
}