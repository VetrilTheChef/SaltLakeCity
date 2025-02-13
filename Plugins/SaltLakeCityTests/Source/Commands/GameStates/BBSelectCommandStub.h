// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Commands/GameStates/Interfaces/IBBSelectCommand.h"
#include "BBSelectCommandStub.generated.h"

/**
 *
 */

UCLASS(NotBlueprintable)

class UBBSelectCommandStub : public UIBBSelectCommand
{
	GENERATED_BODY()

	public:
		UBBSelectCommandStub();

		AIBBGameState * GetGameState();

		virtual void SetGameState(AIBBGameState * NewGameState) override;

		TScriptInterface<IBBSelectable> GetSelectable();

		virtual void SetSelectable(TScriptInterface<IBBSelectable> NewSelectable) override;

		virtual void Execute() override;

		int GetNumExecutions() const;

	protected:
		UPROPERTY()
		AIBBGameState * GameState;

		TScriptInterface<IBBSelectable> Selectable;

		int Executions;
};