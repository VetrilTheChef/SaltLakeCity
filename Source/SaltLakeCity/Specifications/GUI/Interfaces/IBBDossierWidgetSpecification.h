// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "Specifications/GUI/Interfaces/IBBTargetedWidgetSpecification.h"
#include "IBBDossierWidgetSpecification.generated.h"

/**
 *
 */

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBDossierWidgetSpecification : public UIBBTargetedWidgetSpecification
{
	GENERATED_BODY()

	public:
		UIBBDossierWidgetSpecification() : Super() { };

		virtual void SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewTarget) override PURE_VIRTUAL(UIBBDossierWidgetSpecification::SetWidgetTarget, );

		virtual bool Evaluate(const UIBBGUIModel * Model) const override PURE_VIRTUAL(UIBBDossierWidgetSpecification::Evaluate, return false; );

		virtual bool CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const override PURE_VIRTUAL(UIBBDossierWidgetSpecification::CreateWidget, return false; );
};