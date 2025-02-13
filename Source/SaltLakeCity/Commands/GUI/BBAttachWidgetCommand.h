// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "Commands/GUI/Interfaces/IBBAttachWidgetCommand.h"
#include "BBAttachWidgetCommand.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBAttachWidgetCommand : public UIBBAttachWidgetCommand
{
	GENERATED_BODY()

	public:
		UBBAttachWidgetCommand();

		virtual void SetHUD(AIBBHUD * NewHUD) override;

		virtual void SetSpecification(UIBBWidgetSpecification * NewSpecification) override;

		virtual void SetWidgetComponent(UIBBWidgetComponent * NewComponent) override;

		virtual void Execute() override;

	protected:
		UPROPERTY()
		AIBBHUD * HUD;

		UPROPERTY()
		UIBBWidgetSpecification * Specification;

		UPROPERTY()
		UIBBWidgetComponent * Component;
};