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

		float GetValue() const;

		float GetMaxValue() const;

	protected:
		UPROPERTY()
		UIBBDossierEntryModel * Model;

		UPROPERTY()
		UIBBDossierEntryWidget * View;

		FText ValueText;

		float Value;

		float MaxValue;

		void InitializeModel(UIBBDossierEntryModel * DossierEntryModel);
		
		void FinalizeModel();

		void InitializeView(UIBBDossierEntryWidget * DossierEntryView, UIBBDossierEntryModel * DossierEntryModel);

		void FinalizeView();

		UFUNCTION()
		void Update(float NewValue, float NewMaxValue);
};