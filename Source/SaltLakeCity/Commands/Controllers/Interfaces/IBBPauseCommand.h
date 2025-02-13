// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Commands/Controllers/Interfaces/IBBPlayerControllerCommand.h"
#include "IBBPauseCommand.generated.h"

/**
*
*/

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBPauseCommand : public UIBBPlayerControllerCommand
{
	GENERATED_BODY()

	public:
		UIBBPauseCommand() : Super() { };

		virtual void SetController(AIBBPlayerController * NewController) override PURE_VIRTUAL(UIBBPauseCommand::SetController, );

		virtual void Execute() override PURE_VIRTUAL(UIBBPauseCommand::Execute, );
};