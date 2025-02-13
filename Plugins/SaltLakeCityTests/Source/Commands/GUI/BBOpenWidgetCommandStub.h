// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Commands/GUI/Interfaces/IBBOpenWidgetCommand.h"
#include "BBOpenWidgetCommandStub.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable)

class UBBOpenWidgetCommandStub : public UIBBOpenWidgetCommand
{
	GENERATED_BODY()

	public:
		UBBOpenWidgetCommandStub();

		virtual void SetHUD(AIBBHUD * NewHUD) override;

		virtual void SetSpecification(UIBBWidgetSpecification * NewSpecification) override;

		virtual bool GetPopUp() override;

		virtual void SetPopUp(bool NewPopUp) override;

		virtual void Execute() override;

		int GetNumExecutions() const;

	protected:
		UPROPERTY()
		AIBBHUD * HUD;

		UPROPERTY()
		UIBBWidgetSpecification * Specification;

		bool PopUp;

		int Executions;
};