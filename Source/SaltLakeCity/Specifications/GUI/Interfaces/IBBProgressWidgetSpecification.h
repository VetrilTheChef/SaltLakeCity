// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Specifications/GUI/Interfaces/IBBWidgetSpecification.h"
#include "IBBProgressWidgetSpecification.generated.h"

/**
 *
 */

class UIBBProgressComponent;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBProgressWidgetSpecification : public UIBBWidgetSpecification
{
	GENERATED_BODY()

	public:
		UIBBProgressWidgetSpecification() : Super() { };

		virtual void SetComponent(UIBBProgressComponent * NewComponent) PURE_VIRTUAL(UIBBProgressWidgetSpecification::SetComponent, );

		virtual bool Evaluate(const UIBBGUIModel * Model) const override PURE_VIRTUAL(UIBBProgressWidgetSpecification::Evaluate, return false; );

		virtual bool CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const PURE_VIRTUAL(UIBBProgressWidgetSpecification::CreateWidget, return false; );
};