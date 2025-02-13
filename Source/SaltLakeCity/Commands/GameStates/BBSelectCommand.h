// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Commands/GameStates/Interfaces/IBBSelectCommand.h"
#include "BBSelectCommand.generated.h"

/**
 *
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBSelectCommand : public UIBBSelectCommand
{
	GENERATED_BODY()

	public:
		UBBSelectCommand();

		virtual void SetGameState(AIBBGameState * NewGameState) override;

		virtual void SetSelectable(TScriptInterface<IBBSelectable> NewSelectable) override;

		virtual void Execute() override;

	protected:
		UPROPERTY()
		AIBBGameState * GameState;

		TScriptInterface<IBBSelectable> Selectable;
};