// SaltLakeCity 4.27

#include "BBSelectCommandStub.h"

UBBSelectCommandStub::UBBSelectCommandStub() :
	Super()
{
	GameState = nullptr;
	Selectable = TScriptInterface<IBBSelectable>();

	Executions = 0;
}

AIBBGameState * UBBSelectCommandStub::GetGameState()
{
	return GameState;
}

void UBBSelectCommandStub::SetGameState(AIBBGameState * NewGameState)
{
	GameState = NewGameState;
}

TScriptInterface<IBBSelectable> UBBSelectCommandStub::GetSelectable()
{
	return Selectable;
}

void UBBSelectCommandStub::SetSelectable(TScriptInterface<IBBSelectable> NewSelectable)
{
	Selectable = NewSelectable;
}

void UBBSelectCommandStub::Execute()
{
	Executions++;
}

int UBBSelectCommandStub::GetNumExecutions() const
{
	return Executions;
}