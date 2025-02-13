// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Specifications/GUI/Interfaces/IBBWidgetSpecification.h"
#include "BBWidgetSpecification.generated.h"

/**
 *
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBWidgetSpecification : public UIBBWidgetSpecification
{
	GENERATED_BODY()

	public:
		UBBWidgetSpecification();

		virtual void SetWidgetType(EBBWidget NewWidgetType);

		virtual bool Evaluate(const UIBBGUIModel * Model) const override;

		bool CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const override;

	protected:
		EBBWidget WidgetType;

		typedef bool (UBBWidgetSpecification::* WidgetCreator) (UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const;

		TMap<EBBWidget, WidgetCreator> WidgetCreatorsMap;

		bool CreateBuildWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const;

		bool CreateContextWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const;

		bool CreateDateTimeWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const;

		bool CreateJobWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const;

		bool CreateModesWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const;

		bool CreateSelectionWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const;
};
