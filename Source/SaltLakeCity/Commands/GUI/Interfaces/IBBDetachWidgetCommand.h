// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Commands/GUI/Interfaces/IBBGUICommand.h"
#include "IBBDetachWidgetCommand.generated.h"

/**
 * 
 */

class UIBBWidgetComponent;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBDetachWidgetCommand : public UIBBGUICommand
{
	GENERATED_BODY()

	public:
		UIBBDetachWidgetCommand() : Super() { };

		virtual void SetHUD(AIBBHUD * NewHUD) PURE_VIRTUAL(UIBBDetachWidgetCommand::SetHUD, );

		virtual void SetWidgetComponent(UIBBWidgetComponent * NewComponent) PURE_VIRTUAL(UIBBDetachWidgetCommand::SetWidgetComponent, );

		virtual void SetSpecification(UIBBWidgetSpecification * NewSpecification) PURE_VIRTUAL(UIBBDetachWidgetCommand::SetSpecification, );

		virtual void Execute() override PURE_VIRTUAL(UIBBDetachWidgetCommand::Execute, );
};