// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GUI/Models/Interfaces/IBBTargetedModel.h"
#include "IBBTitleModel.generated.h"

/**
 * 
 */

class UIBBTitleWidget;
class UIBBWidgetManager;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBTitleModel : public UIBBTargetedModel
{
	GENERATED_BODY()

	public:
		UIBBTitleModel() : Super() { };

		virtual TScriptInterface<IBBWidgetTarget> GetWidgetTarget() const override
			PURE_VIRTUAL(UIBBTargetModel::GetWidgetTarget, return nullptr; );

		virtual UIBBWidget * GetWidget() const override
			PURE_VIRTUAL(UIBBTitleModel::GetWidget, return nullptr; );

		virtual UIBBWidgetSpecification * GetWidgetSpecification(
			const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory
		) override
			PURE_VIRTUAL(UIBBTitleModel::GetWidgetSpecification, return nullptr; );

		virtual void Initialize(UIBBTitleWidget * NewView, UIBBGUIModel * ParentModel)
			PURE_VIRTUAL(UIBBTitleModel::Initialize, );

		virtual void Finalize()
			PURE_VIRTUAL(UIBBTitleModel::Finalize, );

		virtual void SetPosition(FVector2D NewPosition)
			PURE_VIRTUAL(UIBBTitleModel::SetPosition, );

		virtual UIBBWidget * GetParentWidget() const
			PURE_VIRTUAL(UIBBTitleModel::GetParentWidget, return nullptr; );

		virtual UIBBWidgetSpecification * GetParentWidgetSpecification(
			const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory
		) PURE_VIRTUAL(UIBBTitleModel::GetParentSpecification, return nullptr; );
};