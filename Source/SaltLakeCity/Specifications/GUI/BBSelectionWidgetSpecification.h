// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Specifications/GUI/Interfaces/IBBSelectionWidgetSpecification.h"
#include "BBSelectionWidgetSpecification.generated.h"

/**
 *
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBSelectionWidgetSpecification : public UIBBSelectionWidgetSpecification
{
	GENERATED_BODY()

	public:
		UBBSelectionWidgetSpecification();

		virtual bool Evaluate(const UIBBGUIModel * Model) const override;

		bool CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const override;
};
