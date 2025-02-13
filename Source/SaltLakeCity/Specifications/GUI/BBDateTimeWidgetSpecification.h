// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Specifications/GUI/Interfaces/IBBDateTimeWidgetSpecification.h"
#include "BBDateTimeWidgetSpecification.generated.h"

/**
 *
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBDateTimeWidgetSpecification : public UIBBDateTimeWidgetSpecification
{
	GENERATED_BODY()

	public:
		UBBDateTimeWidgetSpecification();

		virtual bool Evaluate(const UIBBGUIModel * Model) const override;

		bool CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const override;
};
