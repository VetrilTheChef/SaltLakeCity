// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Controllers/Interfaces/IBBSelectionController.h"
#include "BBSelectionController.generated.h"

/**
 * 
 */

class UIBBSelectionModel;
class UIBBSelectionWidget;

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBSelectionController : public UIBBSelectionController
{
	GENERATED_BODY()

	public:
		UBBSelectionController();

		virtual void Initialize(UIBBSelectionWidget * SelectionView, UIBBSelectionModel * SelectionModel) override;

		virtual void Finalize() override;

	protected:
		UPROPERTY()
		UIBBSelectionModel * Model;

		UPROPERTY()
		UIBBSelectionWidget * View;

		void InitializeModel(UIBBSelectionModel * SelectionModel);

		void FinalizeModel();

		void InitializeView(UIBBSelectionWidget * SelectionView);

		void FinalizeView();
};