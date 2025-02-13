// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Commands/Interfaces/IBBCommand.h"
#include "IBBGUICommand.generated.h"

/**
 * 
 */

class AIBBHUD;
class UIBBWidgetSpecification;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBGUICommand : public UIBBCommand
{
	GENERATED_BODY()

	public:
		UIBBGUICommand() : Super() { };

		virtual void SetHUD(AIBBHUD * NewHUD) PURE_VIRTUAL(UIBBGUICommand::SetHUD, );

		virtual void SetSpecification(UIBBWidgetSpecification * NewSpecification) PURE_VIRTUAL(UIBBGUICommand::SetSpecification, );

		virtual void Execute() override PURE_VIRTUAL(UIBBGUICommand::Execute, Super::Execute(); );
};