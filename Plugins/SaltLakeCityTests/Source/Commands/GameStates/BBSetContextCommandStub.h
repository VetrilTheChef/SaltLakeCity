// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Commands/GameStates/Interfaces/IBBSetContextCommand.h"
#include "BBSetContextCommandStub.generated.h"

/**
 *
 */

UCLASS(NotBlueprintable)

class UBBSetContextCommandStub : public UIBBSetContextCommand
{
	GENERATED_BODY()

	public:
		UBBSetContextCommandStub();

		AIBBGameState * GetGameState() const;

		virtual void SetGameState(AIBBGameState * NewGameState) override;

		TScriptInterface<IBBContextualizable> GetContextualizable() const;

		virtual void SetContextualizable(TScriptInterface<IBBContextualizable> NewContextualizable) override;

		virtual void Execute() override;

		int GetNumExecutions();

	protected:
		UPROPERTY()
		AIBBGameState * GameState;

		UPROPERTY()
		TScriptInterface<IBBContextualizable> Contextualizable;

		int Executions;
};