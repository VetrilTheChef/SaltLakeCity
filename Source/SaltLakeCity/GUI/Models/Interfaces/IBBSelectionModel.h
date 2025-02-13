// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Models/Interfaces/IBBGUIModel.h"
#include "IBBSelectionModel.generated.h"

/**
 * 
 */

class AIBBHUD;
class UIBBSelectionWidget;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBSelectionModel : public UIBBGUIModel
{
	GENERATED_BODY()

	public:
		UIBBSelectionModel() : Super() { };

		virtual UIBBWidget * GetWidget() const override PURE_VIRTUAL(UIBBSelectionModel::GetWidget, return nullptr; );

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override PURE_VIRTUAL(UIBBSelectionModel::GetWidgetSpecification, return nullptr; );

		virtual void Initialize(UIBBSelectionWidget * NewView, AIBBHUD * NewHUD) PURE_VIRTUAL(UIBBSelectionModel::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBSelectionModel::Finalize, );
};