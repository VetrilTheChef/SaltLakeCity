// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "IBBWidgetSpecification.generated.h"

/**
 * 
 */

class UIBBGUIModel;
class UIBBWidget;
class UIBBWidgetFactory;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBWidgetSpecification : public UObject
{
	GENERATED_BODY()

	public:
		UIBBWidgetSpecification() : Super() { };

		virtual void SetWidgetType(EBBWidget NewWidgetType) PURE_VIRTUAL(UIBBWidgetSpecification::SetWidgetType, );

		virtual bool Evaluate(const UIBBGUIModel * Model) const PURE_VIRTUAL(UIBBWidgetSpecification::Evaluate, return false; );

		virtual bool CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const PURE_VIRTUAL(UIBBWidgetSpecification::CreateWidget, return false; );
};