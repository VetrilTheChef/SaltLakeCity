// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GUI/Controllers/Interfaces/IBBDossierEntryController.h"
#include "BBDossierEntryController.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBDossierEntryController : public UIBBDossierEntryController
{
	GENERATED_BODY()

	public:
		UBBDossierEntryController();

		virtual void Initialize(UIBBDossierEntryWidget * DossierEntryView, UIBBDossierEntryModel * DossierEntryModel) override;

		virtual void Finalize() override;

	protected:
		UPROPERTY()
		UIBBDossierEntryModel * Model;

		UPROPERTY()
		UIBBDossierEntryWidget * View;

		void InitializeModel(UIBBDossierEntryModel * DossierEntryModel);

		void FinalizeModel();

		void InitializeView(UIBBDossierEntryWidget * DossierEntryView, UIBBDossierEntryModel & DossierEntryModel);

		void FinalizeView();

		UFUNCTION()
		void Update(float NewValue, float NewMaxValue);
};