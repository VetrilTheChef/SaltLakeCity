// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Models/Interfaces/IBBGUIModel.h"
#include "IBBProgressModel.generated.h"

/**
 * 
 */

class UIBBProgressComponent;
class UIBBProgressWidget;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBProgressModel : public UIBBGUIModel
{
	GENERATED_BODY()

	public:
		UIBBProgressModel() : Super() { };

		virtual UIBBWidget * GetWidget() const override PURE_VIRTUAL(UIBBProgressModel::GetWidget, return nullptr; );

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override PURE_VIRTUAL(UIBBProgressModel::GetWidgetSpecification, return nullptr; );

		virtual void Initialize(UIBBProgressWidget * NewView, UIBBProgressComponent * NewProgressComponent) PURE_VIRTUAL(UIBBProgressModel::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBProgressModel::Finalize, );
};