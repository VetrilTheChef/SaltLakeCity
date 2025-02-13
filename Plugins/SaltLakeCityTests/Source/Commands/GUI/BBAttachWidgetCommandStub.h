// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Commands/GUI/Interfaces/IBBAttachWidgetCommand.h"
#include "BBAttachWidgetCommandStub.generated.h"

/**
 * 
 */

class UIBBWidget;

UCLASS(NotBlueprintable)

class UBBAttachWidgetCommandStub : public UIBBAttachWidgetCommand
{
	GENERATED_BODY()

	public:
		UBBAttachWidgetCommandStub();

		UIBBWidget * GetWidget() const;

		void SetWidget(UIBBWidget * NewWidget);

		AIBBHUD * GetHUD() const;

		virtual void SetHUD(AIBBHUD * NewHUD) override;

		UIBBWidgetComponent * GetWidgetComponent() const;

		virtual void SetWidgetComponent(UIBBWidgetComponent * NewComponent) override;

		UIBBWidgetSpecification * GetSpecification() const;

		virtual void SetSpecification(UIBBWidgetSpecification * NewSpecification) override;

		virtual void Execute() override;

		int GetNumExecutions() const;

	protected:
		UPROPERTY()
		UIBBWidget * Widget;

		UPROPERTY()
		AIBBHUD * HUD;

		UPROPERTY()
		UIBBWidgetComponent * Component;

		UPROPERTY()
		UIBBWidgetSpecification * Specification;

		int Executions;
};