// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Commands/GUI/Interfaces/IBBGUICommand.h"
#include "IBBOpenWidgetCommand.generated.h"

/**
 * 
 */

class UIBBWidgetSpecification;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBOpenWidgetCommand : public UIBBGUICommand
{
	GENERATED_BODY()

	public:
		UIBBOpenWidgetCommand() : Super() { };

		virtual void SetHUD(AIBBHUD * NewHUD) PURE_VIRTUAL(UIBBOpenWidgetCommand::SetHUD, );

		virtual void SetSpecification(UIBBWidgetSpecification * NewSpecification) PURE_VIRTUAL(UIBBOpenWidgetCommand::SetSpecification, );

		virtual bool GetPopUp() PURE_VIRTUAL(UIBBOpenWidgetCommand::GetPopUp, return false; );

		virtual void SetPopUp(bool NewPopUp) PURE_VIRTUAL(UIBBOpenWidgetCommand::SetPopUp, );

		virtual void Execute() override PURE_VIRTUAL(UIBBOpenWidgetCommand::Execute, Super::Execute(); );
};