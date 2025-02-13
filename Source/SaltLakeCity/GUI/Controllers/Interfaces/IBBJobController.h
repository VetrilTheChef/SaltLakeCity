// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GUI/Controllers/BBGUIController.h"
#include "IBBJobController.generated.h"

/**
 * 
 */

class UIBBCommandFactory;
class UIBBJobModel;
class UIBBJobWidget;
class UIBBWidgetFactory;
class UIBBWidgetSpecificationFactory;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBJobController : public UBBGUIController
{
	GENERATED_BODY()

	public:
		UIBBJobController() : Super() { };

		virtual void Initialize(UIBBJobWidget * JobView, UIBBJobModel * JobModel, const UIBBWidgetFactory * WidgetFactory, const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, const UIBBCommandFactory * CommandFactory) PURE_VIRTUAL(UIBBJobController::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBJobController::Finalize, );
};