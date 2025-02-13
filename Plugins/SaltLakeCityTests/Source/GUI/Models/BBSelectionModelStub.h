// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Models/Interfaces/IBBSelectionModel.h"
#include "BBSelectionModelStub.generated.h"

/**
 * 
 */

class UIBBSelectionComponent;

UCLASS(NotBlueprintable)

class UBBSelectionModelStub : public UIBBSelectionModel
{
	GENERATED_BODY()

	public:
		UBBSelectionModelStub();

		virtual UIBBWidget * GetWidget() const override;

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override;

		void SetWidgetSpecification(UIBBWidgetSpecification * NewWidgetSpecification);

		virtual void Initialize(UIBBSelectionWidget * NewView, AIBBHUD * NewHUD) override;

		virtual void Finalize() override;

		const UIBBSelectionComponent * GetComponent() const;

	protected:
		UPROPERTY()
		UIBBSelectionWidget * View;

		UPROPERTY()
		AIBBHUD * HUD;

		UPROPERTY()
		const UIBBSelectionComponent * SelectionComponent;

		UPROPERTY()
		UIBBWidgetSpecification * WidgetSpecification;

		UFUNCTION()
		void UpdateSelection(UIBBSelectionComponent * NewSelectionComponent);
};