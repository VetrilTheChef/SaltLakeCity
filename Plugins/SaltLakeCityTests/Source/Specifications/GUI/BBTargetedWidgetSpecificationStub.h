// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Specifications/GUI/Interfaces/IBBTargetedWidgetSpecification.h"
#include "BBTargetedWidgetSpecificationStub.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable)

class UBBTargetedWidgetSpecificationStub : public UIBBTargetedWidgetSpecification
{
	GENERATED_BODY()

	public:
		UBBTargetedWidgetSpecificationStub();

		TScriptInterface<IBBWidgetTarget> GetWidgetTarget();

		virtual void SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewWidgetTarget) override;

		bool GetEvaluation() const;

		void SetEvaluation(bool NewEvaluation, const UIBBGUIModel * NewDesiredModel = nullptr);

		virtual bool Evaluate(const UIBBGUIModel * Model) const override;

		virtual void SetWidget(UIBBWidget * NewWidget);

		virtual bool CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const override;

	protected:
		UPROPERTY()
		const UIBBGUIModel * DesiredModel;

		UPROPERTY()
		TScriptInterface<IBBWidgetTarget> WidgetTarget;

		UPROPERTY()
		UIBBWidget * ReturnWidget;

		bool Evaluation;
};
