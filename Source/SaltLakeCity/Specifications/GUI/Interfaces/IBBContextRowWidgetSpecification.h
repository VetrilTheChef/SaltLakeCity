// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GUI/Data/BBContextRowData.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "Specifications/GUI/Interfaces/IBBTargetedWidgetSpecification.h"
#include "IBBContextRowWidgetSpecification.generated.h"

/**
 *
 */

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBContextRowWidgetSpecification : public UIBBTargetedWidgetSpecification
{
	GENERATED_BODY()

	public:
		UIBBContextRowWidgetSpecification() : Super() { };

		virtual void SetRowData(FBBContextRowData NewRowData) PURE_VIRTUAL(UIBBContextRowWidgetSpecification::SetRowData, );

		virtual void SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewWidgetTarget) override PURE_VIRTUAL(UIBBContextRowWidgetSpecification::SetWidgetTarget, );

		virtual bool Evaluate(const UIBBGUIModel * Model) const override PURE_VIRTUAL(UIBBContextRowWidgetSpecification::Evaluate, return false; );

		virtual bool CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const override PURE_VIRTUAL(UIBBContextRowWidgetSpecification::CreateWidget, return false; );
};