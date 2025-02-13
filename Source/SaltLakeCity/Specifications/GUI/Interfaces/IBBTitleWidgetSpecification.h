// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Specifications/GUI/Interfaces/IBBTargetedWidgetSpecification.h"
#include "IBBTitleWidgetSpecification.generated.h"

/**
 * 
 */

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBTitleWidgetSpecification : public UIBBTargetedWidgetSpecification
{
	GENERATED_BODY()

	public:
		UIBBTitleWidgetSpecification() : Super() { };

		virtual void SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewWidgetTarget) override PURE_VIRTUAL(UIBBTitleWidgetSpecification::SetWidgetTarget, );

		virtual bool Evaluate(const UIBBGUIModel * Model) const override PURE_VIRTUAL(UIBBTitleWidgetSpecification::Evaluate, return false; );

		virtual bool CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const override PURE_VIRTUAL(UIBBTitleWidgetSpecification::CreateWidget, return false; );
};