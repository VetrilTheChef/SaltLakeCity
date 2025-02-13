// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Commands/GUI/Interfaces/IBBDetachWidgetCommand.h"
#include "BBDetachWidgetCommandStub.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable)

class UBBDetachWidgetCommandStub : public UIBBDetachWidgetCommand
{
	GENERATED_BODY()

	public:
		UBBDetachWidgetCommandStub();

		AIBBHUD * GetHUD() const;

		virtual void SetHUD(AIBBHUD * NewHUD) override;

		UIBBWidgetComponent * GetWidgetComponent();

		virtual void SetWidgetComponent(UIBBWidgetComponent * NewComponent) override;

		UIBBWidgetSpecification * GetSpecification();

		virtual void SetSpecification(UIBBWidgetSpecification * NewSpecification) override;

		virtual void Execute() override;

		int GetNumExecutions() const;

	protected:
		UPROPERTY()
		AIBBHUD * HUD;

		UPROPERTY()
		UIBBWidgetComponent * Component;

		UPROPERTY()
		UIBBWidgetSpecification * Specification;

		int Executions;
};