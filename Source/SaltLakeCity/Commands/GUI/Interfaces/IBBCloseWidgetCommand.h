// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Commands/GUI/Interfaces/IBBGUICommand.h"
#include "IBBCloseWidgetCommand.generated.h"

/**
 * 
 */

class UIBBWidgetSpecification;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBCloseWidgetCommand : public UIBBGUICommand
{
	GENERATED_BODY()

	public:
		UIBBCloseWidgetCommand() : Super() { };

		virtual void SetHUD(AIBBHUD * NewHUD) PURE_VIRTUAL(UIBBCloseWidgetCommand::SetHUD, );

		virtual void SetSpecification(UIBBWidgetSpecification * NewSpecification) PURE_VIRTUAL(UIBBCloseWidgetCommand::SetSpecification, );

		virtual void Execute() override PURE_VIRTUAL(UIBBCloseWidgetCommand::Execute, );
};