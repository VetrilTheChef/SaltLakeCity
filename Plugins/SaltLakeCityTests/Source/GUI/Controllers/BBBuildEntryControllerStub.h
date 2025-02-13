// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Controllers/Interfaces/IBBBuildEntryController.h"
#include "BBBuildEntryControllerStub.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable)

class UBBBuildEntryControllerStub : public UIBBBuildEntryController
{
	GENERATED_BODY()

	public:
		UBBBuildEntryControllerStub();

		virtual void Initialize(UIBBBuildEntryWidget * BuildEntryView, UIBBBuildEntryModel * BuildEntryModel, const UIBBCommandFactory * CommandFactory) override;

		virtual void Finalize() override;

	protected:
		UPROPERTY()
		UIBBBuildEntryModel * Model;

		UPROPERTY()
		UIBBBuildEntryWidget * View;

		void InitializeModel(UIBBBuildEntryModel * BuildEntryModel);
		
		void FinalizeModel();

		void InitializeView(UIBBBuildEntryWidget * BuildEntryView, UIBBBuildEntryModel * BuildEntryModel, const UIBBCommandFactory * CommandFactory);

		void FinalizeView();
};