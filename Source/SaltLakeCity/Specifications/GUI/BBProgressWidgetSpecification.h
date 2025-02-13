// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Specifications/GUI/Interfaces/IBBProgressWidgetSpecification.h"
#include "BBProgressWidgetSpecification.generated.h"

/**
 *
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBProgressWidgetSpecification : public UIBBProgressWidgetSpecification
{
	GENERATED_BODY()

	public:
		UBBProgressWidgetSpecification();

		virtual void SetComponent(UIBBProgressComponent * NewComponent) override;

		virtual bool Evaluate(const UIBBGUIModel * Model) const override;

		bool CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const override;

	protected:
		UPROPERTY()
		UIBBProgressComponent * Component;
};
