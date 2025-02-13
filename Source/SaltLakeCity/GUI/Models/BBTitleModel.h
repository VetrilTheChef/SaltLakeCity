// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Models/Interfaces/IBBTitleModel.h"
#include "BBTitleModel.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBTitleModel : public UIBBTitleModel
{
	GENERATED_BODY()

	public:
		UBBTitleModel();

		virtual TScriptInterface<IBBWidgetTarget> GetWidgetTarget() const override;

		virtual UIBBWidget * GetWidget() const override;

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override;

		virtual void Initialize(UIBBTitleWidget * NewView, UIBBGUIModel * NewParentModel, AIBBHUD * NewHUD) override;

		virtual void Finalize() override;

		virtual void SetPosition(FVector2D NewPosition) override;

		virtual UIBBWidget * GetParentWidget() const override;

		virtual UIBBWidgetSpecification * GetParentWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override;

	protected:
		UPROPERTY()
		UIBBTitleWidget * View;

		UPROPERTY()
		UIBBGUIModel * ParentModel;

		UPROPERTY()
		AIBBHUD * HUD;

		void InitializeView(UIBBTitleWidget * NewView);

		void InitializeParentModel(UIBBGUIModel * NewParentModel);

		void InitializeHUD(AIBBHUD * NewHUD);

		void FinalizeView();

		void FinalizeParentModel();

		void FinalizeHUD();
};