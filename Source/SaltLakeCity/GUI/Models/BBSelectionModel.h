// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GUI/Models/Interfaces/IBBSelectionModel.h"
#include "BBSelectionModel.generated.h"

/**
 * 
 */

class IBBWidgetTarget;
class UIBBSelectionComponent;

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBSelectionModel : public UIBBSelectionModel
{
	GENERATED_BODY()

	public:
		UBBSelectionModel();

		virtual UIBBWidget * GetWidget() const override;

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override;

		virtual void Initialize(UIBBSelectionWidget * NewView, AIBBHUD * NewHUD) override;

		virtual void Finalize() override;

	protected:
		UPROPERTY()
		UIBBSelectionWidget * View;

		UPROPERTY()
		AIBBHUD * HUD;

		UPROPERTY()
		UIBBSelectionComponent * Component;

		void InitializeView(UIBBSelectionWidget * NewView);

		void InitializeHUD(AIBBHUD * NewHUD);

		void InitializeComponent(UIBBSelectionComponent * NewSelectionComponent);

		void FinalizeView();

		void FinalizeHUD();

		void FinalizeComponent();

		UFUNCTION()
		void UpdateComponent(UIBBSelectionComponent * NewSelectionComponent);

		UFUNCTION()
		void UpdateWidgetTarget(const TScriptInterface<IBBWidgetTarget> NewWidgetTarget);
};