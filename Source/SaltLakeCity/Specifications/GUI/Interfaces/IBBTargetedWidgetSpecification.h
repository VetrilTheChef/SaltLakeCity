// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Specifications/GUI/Interfaces/IBBWidgetSpecification.h"
#include "IBBTargetedWidgetSpecification.generated.h"

/**
 * 
 */

class IBBWidgetTarget;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBTargetedWidgetSpecification : public UIBBWidgetSpecification
{
	GENERATED_BODY()

	public:
		UIBBTargetedWidgetSpecification() : Super() { };

		UFUNCTION()
		virtual void SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewWidgetTarget) PURE_VIRTUAL(UIBBTargetedWidgetSpecification::SetWidgetTarget, );

		virtual bool Evaluate(const UIBBGUIModel * Model) const override PURE_VIRTUAL(UIBBTargetedWidgetSpecification::Evaluate, return false; );

		virtual bool CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const override PURE_VIRTUAL(UIBBTargetedWidgetSpecification::CreateWidget, return false; );
};