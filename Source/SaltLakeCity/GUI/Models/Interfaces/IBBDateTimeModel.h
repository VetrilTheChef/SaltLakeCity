// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Models/Interfaces/IBBGUIModel.h"
#include "IBBDateTimeModel.generated.h"

/**
 * 
 */

class UIBBDateTimeWidget;
class UIBBGameClock;
class UIBBWidget;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBDateTimeModel : public UIBBGUIModel
{
	GENERATED_BODY()

	public:
		UIBBDateTimeModel() : Super() { };

		virtual UIBBWidget * GetWidget() const override PURE_VIRTUAL(UIBBDateTimeModel::GetWidget, return nullptr; );

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override PURE_VIRTUAL(UIBBDateTimeModel::GetWidgetSpecification, return nullptr; );

		virtual void Initialize(UIBBDateTimeWidget * NewView, UIBBGameClock * NewGameClock) PURE_VIRTUAL(UIBBDateTimeModel::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBDateTimeModel::Finalize, );
};