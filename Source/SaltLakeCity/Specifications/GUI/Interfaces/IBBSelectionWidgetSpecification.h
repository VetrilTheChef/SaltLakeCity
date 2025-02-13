// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "Specifications/GUI/Interfaces/IBBWidgetSpecification.h"
#include "IBBSelectionWidgetSpecification.generated.h"

/**
 *
 */

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBSelectionWidgetSpecification : public UIBBWidgetSpecification
{
	GENERATED_BODY()

	public:
		UIBBSelectionWidgetSpecification() : Super() { };

		virtual bool Evaluate(const UIBBGUIModel * Model) const override PURE_VIRTUAL(UIBBSelectionWidgetSpecification::Evaluate, return false; );

		virtual bool CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const override PURE_VIRTUAL(UIBBSelectionWidgetSpecification::CreateWidget, return false; );
};