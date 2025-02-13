// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Specifications/GUI/Interfaces/IBBTargetedWidgetSpecification.h"
#include "BBTargetedWidgetSpecification.generated.h"

/**
 *
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBTargetedWidgetSpecification : public UIBBTargetedWidgetSpecification
{
	GENERATED_BODY()

	public:
		UBBTargetedWidgetSpecification();

		virtual void SetWidgetType(EBBWidget NewWidgetType) override;

		virtual void SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewWidgetTarget) override;

		virtual bool Evaluate(const UIBBGUIModel * Model) const override;

		bool CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const override;

	protected:
		UPROPERTY()
		TScriptInterface<IBBWidgetTarget> WidgetTarget;

		EBBWidget WidgetType;

		typedef bool (UBBTargetedWidgetSpecification::* WidgetCreator) (UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const;

		TMap<EBBWidget, WidgetCreator> WidgetCreatorsMap;

		bool CreateDossierWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const;

		bool CreateProgressWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const;

		bool CreateTitleWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const;
};
