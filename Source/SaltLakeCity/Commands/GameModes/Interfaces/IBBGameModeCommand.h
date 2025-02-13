// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Commands/Interfaces/IBBCommand.h"
#include "GameModes/Includes/BBGameModeEnum.h"
#include "IBBGameModeCommand.generated.h"

/**
 * 
 */

class AIBBGameMode;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBGameModeCommand : public UIBBCommand
{
	GENERATED_BODY()

	public:
		UIBBGameModeCommand() : Super() { };

		virtual void SetGameMode(AIBBGameMode * NewGameMode) PURE_VIRTUAL(UIBBOpenWidgetCommand::SetGameMode, );

		virtual void SetActiveGameMode(EBBGameMode NewActiveGameMode) PURE_VIRTUAL(UIBBGameModeCommand::SetActiveGameMode, );

		virtual void Execute() override PURE_VIRTUAL(UIBBGameModeCommand::Execute, );
};