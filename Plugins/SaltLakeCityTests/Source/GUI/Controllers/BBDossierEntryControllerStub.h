// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GUI/Controllers/Interfaces/IBBDossierEntryController.h"
#include "BBDossierEntryControllerStub.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable)

class UBBDossierEntryControllerStub : public UIBBDossierEntryController
{
	GENERATED_BODY()

	public:
		UBBDossierEntryControllerStub();

		virtual void Initialize(UIBBDossierEntryWidget * DossierEntryView, UIBBDossierEntryModel * DossierEntryModel) override;

		virtual void Finalize() override;

	protected:
		UPROPERTY()
		UIBBDossierEntryModel * Model;

		UPROPERTY()
		UIBBDossierEntryWidget * View;

		void InitializeModel(UIBBDossierEntryModel * DossierEntryModel);
		
		void FinalizeModel();

		void InitializeView(UIBBDossierEntryWidget * DossierEntryView, UIBBDossierEntryModel * DossierEntryModel);

		void FinalizeView();
};