// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Specifications/GUI/Interfaces/IBBDossierWidgetSpecification.h"
#include "BBDossierWidgetSpecification.generated.h"

/**
 *
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBDossierWidgetSpecification : public UIBBDossierWidgetSpecification
{
	GENERATED_BODY()

	public:
		UBBDossierWidgetSpecification();

		virtual void SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewWidgetTarget) override;
		
		virtual bool Evaluate(const UIBBGUIModel * Model) const override;

		bool CreateWidget(UIBBWidget * & Widget, const UIBBWidgetFactory & WidgetFactory) const override;

	protected:
		UPROPERTY()
		TScriptInterface<IBBWidgetTarget> WidgetTarget;
};
