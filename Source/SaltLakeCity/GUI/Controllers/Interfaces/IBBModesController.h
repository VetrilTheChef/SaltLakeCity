// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Controllers/BBGUIController.h"
#include "IBBModesController.generated.h"

/**
 * 
 */

class UIBBCommandFactory;
class UIBBModesModel;
class UIBBModesWidget;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBModesController : public UBBGUIController
{
	GENERATED_BODY()

	public:
		UIBBModesController() : Super() { };

		virtual void Initialize(UIBBModesWidget * ModesView, UIBBModesModel * ModesModel, const UIBBCommandFactory * CommandFactory) PURE_VIRTUAL(UIBBModesController::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBModesController::Finalize, );
};