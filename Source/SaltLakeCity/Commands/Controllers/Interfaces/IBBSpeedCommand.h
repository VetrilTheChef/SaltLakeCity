// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Commands/Controllers/Interfaces/IBBPlayerControllerCommand.h"
#include "IBBSpeedCommand.generated.h"

/**
 * 
 */

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBSpeedCommand : public UIBBPlayerControllerCommand
{
	GENERATED_BODY()

	public:
		UIBBSpeedCommand() : Super() { };

		virtual void SetController(AIBBPlayerController * NewController) override PURE_VIRTUAL(UIBBSpeedCommand::SetController, );

		virtual void SetWorldSettings(AWorldSettings * NewWorldSettings) PURE_VIRTUAL(UIBBSpeedCommand::SetWorldSettings, );

		virtual float GetTimeDilation() PURE_VIRTUAL(UIBBSpeedCommand::GetTimeDilation, return 1.0f; );

		virtual void SetTimeDilation(float NewTimeDilation) PURE_VIRTUAL(UIBBSpeedCommand::SetTimeDilation, );

		virtual void Execute() override PURE_VIRTUAL(UIBBSpeedCommand::Execute, );
};