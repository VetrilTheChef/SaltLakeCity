// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GUI/Controllers/BBGUIController.h"
#include "IBBDossierEntryController.generated.h"

/**
 * 
 */

class UIBBDossierEntryModel;
class UIBBDossierEntryWidget;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBDossierEntryController : public UBBGUIController
{
	GENERATED_BODY()

	public:
		UIBBDossierEntryController() : Super() { };

		virtual void Initialize(UIBBDossierEntryWidget * DossierEntryView, UIBBDossierEntryModel * DossierEntryModel) PURE_VIRTUAL(UIBBDossierEntryController::Initialize, );
		
		virtual void Finalize() PURE_VIRTUAL(UIBBDossierEntryController::Finalize, );
};