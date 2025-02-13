// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Commands/GameStates/Interfaces/IBBSetContextCommand.h"
#include "BBSetContextCommand.generated.h"

/**
 *
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBSetContextCommand : public UIBBSetContextCommand
{
	GENERATED_BODY()

	public:
		UBBSetContextCommand();

		virtual void SetGameState(AIBBGameState * NewGameState) override;

		virtual void SetContextualizable(TScriptInterface<IBBContextualizable> NewContextualizable) override;

		virtual void Execute() override;

	protected:
		UPROPERTY()
		AIBBGameState * GameState;

		UPROPERTY()
		TScriptInterface<IBBContextualizable> Contextualizable;
};