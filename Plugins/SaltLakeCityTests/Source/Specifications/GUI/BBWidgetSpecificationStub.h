// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Specifications/GUI/Interfaces/IBBWidgetSpecification.h"
#include "BBWidgetSpecificationStub.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable)

class UBBWidgetSpecificationStub : public UIBBWidgetSpecification
{
	GENERATED_BODY()

	public:
		UBBWidgetSpecificationStub();

		bool GetEvaluation() const;

		void SetEvaluation(bool NewEvaluation, const UIBBGUIModel * NewDesiredModel = nullptr);

		virtual bool Evaluate(const UIBBGUIModel * Model) const override;

		virtual void SetWidget(UIBBWidget * NewWidget);

		virtual bool CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const override;

	protected:
		UPROPERTY()
		const UIBBGUIModel * DesiredModel;

		UPROPERTY()
		UIBBWidget * ReturnWidget;

		bool Evaluation;
};
