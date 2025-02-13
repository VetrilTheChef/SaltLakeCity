// SaltLakeCity 4.27

#include "BBSetContextCommandStub.h"

UBBSetContextCommandStub::UBBSetContextCommandStub() :
	Super()
{
	GameState = nullptr;
	Contextualizable = TScriptInterface<IBBContextualizable>();

	Executions = 0;
}

AIBBGameState * UBBSetContextCommandStub::GetGameState() const
{
	return GameState;
}

void UBBSetContextCommandStub::SetGameState(AIBBGameState * NewGameState)
{
	GameState = NewGameState;
}

TScriptInterface<IBBContextualizable> UBBSetContextCommandStub::GetContextualizable() const
{
	return Contextualizable;
}

void UBBSetContextCommandStub::SetContextualizable(TScriptInterface<IBBContextualizable> NewContextualizable)
{
	Contextualizable = NewContextualizable;
}

void UBBSetContextCommandStub::Execute()
{
	Executions++;
}

int UBBSetContextCommandStub::GetNumExecutions()
{
	return Executions;
}