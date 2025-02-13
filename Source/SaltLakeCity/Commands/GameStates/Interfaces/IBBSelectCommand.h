// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Commands/GUI/Interfaces/IBBGUICommand.h"
#include "IBBSelectCommand.generated.h"

/**
 *
 */

class AIBBGameState;
class IBBSelectable;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBSelectCommand : public UIBBCommand
{
	GENERATED_BODY()

	public:
		UIBBSelectCommand() : Super() { };
		
		virtual void SetGameState(AIBBGameState * NewGameState) PURE_VIRTUAL(UIBBSelectCommand::SetGameState, );

		virtual void SetSelectable(TScriptInterface<IBBSelectable> NewSelectable) PURE_VIRTUAL(UIBBSelectCommand::SetSelectable, );

		virtual void Execute() override PURE_VIRTUAL (UIBBSelectCommand::Execute, );
};