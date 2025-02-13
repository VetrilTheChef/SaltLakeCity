// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Specifications/GUI/Interfaces/IBBContextRowWidgetSpecification.h"
#include "BBContextRowWidgetSpecification.generated.h"

/**
 *
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBContextRowWidgetSpecification : public UIBBContextRowWidgetSpecification
{
	GENERATED_BODY()

	public:
		UBBContextRowWidgetSpecification();

		virtual void SetRowData(FBBContextRowData NewRowData) override;

		virtual void SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewWidgetTarget) override;

		virtual bool Evaluate(const UIBBGUIModel * Model) const override;

		bool CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const override;

	protected:
		UPROPERTY()
		TScriptInterface<IBBWidgetTarget> WidgetTarget;

		FBBContextRowData RowData;
};
