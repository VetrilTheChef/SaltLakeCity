// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Commands/GUI/Interfaces/IBBCloseWidgetCommand.h"
#include "BBCloseWidgetCommandStub.generated.h"

/**
 * 
 */

class UIBBWidgetSpecification;

UCLASS(NotBlueprintable)

class UBBCloseWidgetCommandStub : public UIBBCloseWidgetCommand
{
	GENERATED_BODY()

	public:
		UBBCloseWidgetCommandStub();

		UIBBWidgetSpecification * GetSpecification();

		virtual void SetSpecification(UIBBWidgetSpecification * NewSpecification);

		virtual void Execute() override;

		int GetNumExecutions() const;

	protected:
		UPROPERTY()
		UIBBWidgetSpecification * Specification;

		int Executions;
};