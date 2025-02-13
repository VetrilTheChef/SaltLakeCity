// SaltLakeCity 4.26

#include "BBSelectCommand.h"
#include "Actors/Components/Interfaces/IBBActorComponent.h"
#include "GameStates/Interfaces/IBBGameState.h"

UBBSelectCommand::UBBSelectCommand() :
	Super()
{
	GameState = nullptr;
	Selectable = TScriptInterface<IBBSelectable>();
}

void UBBSelectCommand::SetGameState(AIBBGameState * NewGameState)
{
	verifyf(IsValid(NewGameState), TEXT("New Game State is invalid."));

	GameState = NewGameState;
}

void UBBSelectCommand::SetSelectable(TScriptInterface<IBBSelectable> NewSelectable)
{
	Selectable = NewSelectable;
}

void UBBSelectCommand::Execute()
{
	verifyf(IsValid(GameState), TEXT("Game State is invalid."));

	GameState->SetSelection(Forward<TScriptInterface<IBBSelectable>>(Selectable));
}