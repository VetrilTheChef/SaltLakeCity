// SaltLakeCity 4.27

#include "BBSetContextCommand.h"
#include "Actors/Interfaces/IBBContextualizable.h"
#include "GameStates/Interfaces/IBBGameState.h"

UBBSetContextCommand::UBBSetContextCommand() :
	Super()
{
	GameState = nullptr;
	Contextualizable = TScriptInterface<IBBContextualizable>();
}

void UBBSetContextCommand::SetGameState(AIBBGameState * NewGameState)
{
	verifyf(IsValid(NewGameState), TEXT("New Game State is invalid."));

	GameState = NewGameState;
}

void UBBSetContextCommand::SetContextualizable(TScriptInterface<IBBContextualizable> NewContextualizable)
{
	Contextualizable = NewContextualizable;
}

void UBBSetContextCommand::Execute()
{
	verifyf(IsValid(GameState), TEXT("Game State is invalid."));

	GameState->SetContext(Forward<TScriptInterface<IBBContextualizable>>(Contextualizable));
}