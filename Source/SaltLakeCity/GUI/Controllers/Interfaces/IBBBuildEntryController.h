// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Controllers/BBGUIController.h"
#include "IBBBuildEntryController.generated.h"

/**
 * 
 */

class UIBBBuildEntryModel;
class UIBBBuildEntryWidget;
class UIBBCommandFactory;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBBuildEntryController : public UBBGUIController
{
	GENERATED_BODY()

	public:
		UIBBBuildEntryController() : Super() { };

		virtual void Initialize(UIBBBuildEntryWidget * BuildEntryView, UIBBBuildEntryModel * BuildEntryModel, const UIBBCommandFactory * CommandFactory) PURE_VIRTUAL(UIBBBuildEntryController::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBBuildEntryController::Finalize, );
};