// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "Commands/GUI/Interfaces/IBBOpenWidgetCommand.h"
#include "BBOpenWidgetCommand.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBOpenWidgetCommand : public UIBBOpenWidgetCommand
{
	GENERATED_BODY()

	public:
		UBBOpenWidgetCommand();

		virtual void SetHUD(AIBBHUD * NewHUD) override;

		virtual void SetSpecification(UIBBWidgetSpecification * NewSpecification) override;

		virtual bool GetPopUp() override;

		virtual void SetPopUp(bool NewPopUp) override;

		virtual void Execute() override;

	protected:
		UPROPERTY()
		AIBBHUD * HUD;

		UPROPERTY()
		UIBBWidgetSpecification * Specification;

		bool PopUp;
};