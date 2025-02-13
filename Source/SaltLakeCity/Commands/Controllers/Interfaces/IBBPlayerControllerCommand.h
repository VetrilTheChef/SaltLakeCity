// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Commands/Interfaces/IBBCommand.h"
#include "IBBPlayerControllerCommand.generated.h"

/**
 * 
 */

class AIBBPlayerController;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBPlayerControllerCommand : public UIBBCommand
{
	GENERATED_BODY()

	public:
		UIBBPlayerControllerCommand() : Super() { };

		virtual void SetController(AIBBPlayerController * NewController) PURE_VIRTUAL(UIBBPlayerControllerCommand::SetController, );

		virtual void Execute() override PURE_VIRTUAL(UIBBPlayerControllerCommand::Execute, );
};