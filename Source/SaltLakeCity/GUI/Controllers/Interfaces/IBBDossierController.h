// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Controllers/BBGUIController.h"
#include "IBBDossierController.generated.h"

/**
 * 
 */

class UIBBCommandFactory;
class UIBBDossierModel;
class UIBBDossierWidget;
class UIBBSpecificationFactory;
class UIBBWidgetFactory;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBDossierController : public UBBGUIController
{
	GENERATED_BODY()

	public:
		UIBBDossierController() : Super() { };

		virtual void Initialize(UIBBDossierWidget * DossierView, UIBBDossierModel * DossierModel, const UIBBWidgetFactory * WidgetFactory, const UIBBSpecificationFactory * SpecificationFactory, const UIBBCommandFactory * CommandFactory) PURE_VIRTUAL(UIBBDossierWidget::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBDossierWidget::Finalize, );
};
