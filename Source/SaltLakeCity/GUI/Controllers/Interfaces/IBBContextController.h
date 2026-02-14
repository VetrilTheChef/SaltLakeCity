// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GUI/Controllers/BBGUIController.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "IBBContextController.generated.h"

/**
 * 
 */

class UIBBCommandFactory;
class UIBBContextModel;
class UIBBContextWidget;
class UIBBWidgetSpecificationFactory;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBContextController : public UBBGUIController
{
	GENERATED_BODY()

	public:
		UIBBContextController() : Super() { };

		virtual void Initialize(
			UIBBContextWidget * ContextView,
			UIBBContextModel * ContextModel,
			const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory,
			const UIBBCommandFactory * CommandFactory)
		PURE_VIRTUAL(UIBBContextController::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBContextController::Finalize, );
};