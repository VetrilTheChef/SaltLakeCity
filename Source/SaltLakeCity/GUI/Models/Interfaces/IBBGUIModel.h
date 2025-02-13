// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IBBGUIModel.generated.h"

/**
 * 
 */

class UIBBWidget;
class UIBBWidgetSpecification;
class UIBBWidgetSpecificationFactory;

UCLASS()

class SALTLAKECITY_API UIBBGUIModel : public UObject
{
	GENERATED_BODY()
		
	public:
		UIBBGUIModel() : Super() { };

		virtual UIBBWidget * GetWidget() const PURE_VIRTUAL(UIBBGUIModel::GetWidget, return nullptr; );

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) PURE_VIRTUAL(UIBBGUIModel::GetWidgetSpecification, return nullptr; );
};