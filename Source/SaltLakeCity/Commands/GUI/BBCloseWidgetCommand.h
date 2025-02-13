// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Commands/GUI/Interfaces/IBBCloseWidgetCommand.h"
#include "BBCloseWidgetCommand.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBCloseWidgetCommand : public UIBBCloseWidgetCommand
{
	GENERATED_BODY()

	public:
		UBBCloseWidgetCommand();

		virtual void SetHUD(AIBBHUD * NewHUD) override;

		virtual void SetSpecification(UIBBWidgetSpecification * NewSpecification);

		virtual void Execute() override;

	protected:
		UPROPERTY()
		AIBBHUD * HUD;

		UPROPERTY()
		UIBBWidgetSpecification * Specification;
};