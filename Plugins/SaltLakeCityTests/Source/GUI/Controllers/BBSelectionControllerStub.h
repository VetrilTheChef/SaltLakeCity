// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Controllers/Interfaces/IBBSelectionController.h"
#include "BBSelectionControllerStub.generated.h"

/**
 * 
 */

class UIBBSelectionModel;
class UIBBSelectionWidget;
class UIBBWidgetComponent;

UCLASS(NotBlueprintable)

class UBBSelectionControllerStub : public UIBBSelectionController
{
	GENERATED_BODY()

	public:
		UBBSelectionControllerStub();

		virtual void Initialize(UIBBSelectionWidget * SelectionView, UIBBSelectionModel * SelectionModel) override;

		virtual void Finalize() override;

	protected:
		UPROPERTY()
		UIBBSelectionWidget * View;

		UPROPERTY()
		UIBBSelectionModel * Model;

		void InitializeView(UIBBSelectionWidget * SelectionView);

		void FinalizeView();

		void InitializeModel(UIBBSelectionModel * SelectionModel);

		void FinalizeModel();
};