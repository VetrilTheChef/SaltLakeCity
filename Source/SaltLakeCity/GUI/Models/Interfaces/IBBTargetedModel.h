// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GUI/Models/Interfaces/IBBGUIModel.h"
#include "IBBTargetedModel.generated.h"

/**
 * 
 */

class IBBWidgetTarget;
class UIBBWidget;

UCLASS()

class SALTLAKECITY_API UIBBTargetedModel : public UIBBGUIModel
{
	GENERATED_BODY()
		
	public:
		UIBBTargetedModel() : Super() { };

		virtual TScriptInterface<IBBWidgetTarget> GetWidgetTarget() const PURE_VIRTUAL(UIBBTargetModel::GetTarget, return TScriptInterface<IBBWidgetTarget>(); );

		virtual UIBBWidget * GetWidget() const override PURE_VIRTUAL(UIBBTargetModel::GetWidget, return nullptr; );

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override PURE_VIRTUAL(UIBBTargetModel::GetWidgetSpecification, return nullptr; );

		DECLARE_EVENT_OneParam(UIBBTargetModel, FUpdateTarget, TScriptInterface<IBBWidgetTarget>);

		FUpdateTarget & OnTargetUpdate() { return TargetUpdated; };

	protected:
		FUpdateTarget TargetUpdated;
};