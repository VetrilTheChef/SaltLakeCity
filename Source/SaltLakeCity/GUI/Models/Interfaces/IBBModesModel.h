// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Models/Interfaces/IBBGUIModel.h"
#include "IBBModesModel.generated.h"

/**
 *
 */

class AIBBGameMode;
class UIBBModesWidget;
class UIBBWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIBBModesModel_ModeUpdate, EBBGameMode, NewGameMode);

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBModesModel : public UIBBGUIModel
{
	GENERATED_BODY()

	public:
		UIBBModesModel() : Super() { };

		virtual UIBBWidget * GetWidget() const override PURE_VIRTUAL(UIBBModesModel::GetWidget, return nullptr; );

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override PURE_VIRTUAL(UIBBModesModel::GetWidgetSpecification, return nullptr; );

		virtual void Initialize(UIBBModesWidget * NewView, AIBBGameMode * NewGameMode) PURE_VIRTUAL(UIBBModesModel::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBModesModel::Finalize, );

		FIBBModesModel_ModeUpdate OnModeUpdate;
};