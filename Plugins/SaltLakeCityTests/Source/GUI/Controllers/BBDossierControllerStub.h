// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "Attributes/Includes/BBAttributeEnum.h"
#include "Attributes/Includes/BBNeedEnum.h"
#include "Attributes/Includes/BBSkillEnum.h"
#include "GUI/Controllers/Interfaces/IBBDossierController.h"
#include "BBDossierControllerStub.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable)

class UBBDossierControllerStub : public UIBBDossierController
{
	GENERATED_BODY()

	public:
		UBBDossierControllerStub();

		virtual void PostInitProperties() override;

		virtual void BeginDestroy() override;

		virtual void Initialize(UIBBDossierWidget * DossierView, UIBBDossierModel * DossierModel, const UIBBWidgetFactory * WidgetFactory, const UIBBSpecificationFactory * SpecificationFactory, const UIBBCommandFactory * CommandFactory) override;

		virtual void Finalize() override;

		FText GetDisplayName();
	
	protected:
		UPROPERTY()
		UIBBDossierModel * Model;

		UPROPERTY()
		UIBBDossierWidget * View;

		FText DisplayName;

		void InitializeModel(UIBBDossierModel * DossierModel);

		void FinalizeModel();

		void InitializeView(UIBBDossierWidget * DossierView);

		void FinalizeView();

		UFUNCTION()
		void UpdateDisplayName(FText NewDisplayName);
};
