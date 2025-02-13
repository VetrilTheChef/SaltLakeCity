// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "Specifications/GUI/Interfaces/IBBTargetedWidgetSpecification.h"
#include "IBBJobWidgetSpecification.generated.h"

/**
 *
 */

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBJobWidgetSpecification : public UIBBTargetedWidgetSpecification
{
	GENERATED_BODY()

	public:
		UIBBJobWidgetSpecification() : Super() { };

		virtual void SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewWidgetTarget) override PURE_VIRTUAL(UIBBJobWidgetSpecification::SetWidgetTarget, );

		virtual bool Evaluate(const UIBBGUIModel * Model) const override PURE_VIRTUAL(UIBBJobWidgetSpecification::Evaluate, return false; );

		virtual bool CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const override PURE_VIRTUAL(UIBBJobWidgetSpecification::CreateWidget, return false; );
};