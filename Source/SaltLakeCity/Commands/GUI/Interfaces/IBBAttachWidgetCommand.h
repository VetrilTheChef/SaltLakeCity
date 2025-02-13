// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Commands/GUI/Interfaces/IBBGUICommand.h"
#include "IBBAttachWidgetCommand.generated.h"

/**
 * 
 */

class UIBBWidgetComponent;
class UIBBWidgetSpecification;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBAttachWidgetCommand : public UIBBGUICommand
{
	GENERATED_BODY()

	public:
		UIBBAttachWidgetCommand() : Super() { };

		virtual void SetHUD(AIBBHUD * NewHUD) PURE_VIRTUAL(UIBBAttachWidgetCommand::SetHUD, );

		virtual void SetWidgetComponent(UIBBWidgetComponent * NewComponent) PURE_VIRTUAL(UIBBAttachWidgetCommand::SetWidgetComponent, );

		virtual void SetSpecification(UIBBWidgetSpecification * NewSpecification) PURE_VIRTUAL(UIBBAttachWidgetCommand::SetSpecification, );

		virtual void Execute() override PURE_VIRTUAL(UIBBAttachWidgetCommand::Execute, Super::Execute(); );
};