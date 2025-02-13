// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Commands/Interfaces/IBBCommand.h"
#include "IBBSetContextCommand.generated.h"

/**
 *
 */

class AIBBGameState;
class IBBContextualizable;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBSetContextCommand : public UIBBCommand
{
	GENERATED_BODY()

	public:
		UIBBSetContextCommand() : Super() { };
		
		virtual void SetGameState(AIBBGameState * NewGameState) PURE_VIRTUAL(UIBBSetContextCommand::SetGameState, );

		virtual void SetContextualizable(TScriptInterface<IBBContextualizable> NewContextualizable) PURE_VIRTUAL(UIBBSetContextCommand::SetContextualizable, );

		virtual void Execute() override PURE_VIRTUAL (UIBBSetContextCommand::Execute, );
};