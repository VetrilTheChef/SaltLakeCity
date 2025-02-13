// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Controllers/BBGUIController.h"
#include "IBBSelectionController.generated.h"

/**
 * 
 */

class UIBBSelectionModel;
class UIBBSelectionWidget;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBSelectionController : public UBBGUIController
{
	GENERATED_BODY()

	public:
		UIBBSelectionController() : Super() { };

		virtual void Initialize(UIBBSelectionWidget * SelectionView, UIBBSelectionModel * SelectionModel) PURE_VIRTUAL(UIBBSelectionController::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBSelectionController::Finalize, );
};