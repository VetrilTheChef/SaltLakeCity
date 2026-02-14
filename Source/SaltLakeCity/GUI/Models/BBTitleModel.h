// SaltLakeCity 5.7

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

		virtual UIBBWidgetSpecification * GetWidgetSpecification(
			const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory
		) override;

		virtual void Initialize(UIBBTitleWidget * NewView, UIBBGUIModel * NewParentModel) override;

		virtual void Finalize() override;

		virtual void SetPosition(FVector2D NewPosition) override;

		virtual UIBBWidget * GetParentWidget() const override;

		virtual UIBBWidgetSpecification * GetParentWidgetSpecification(
			const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory
		) override;

	protected:
		void InitializeView(UIBBTitleWidget * NewView);

		void InitializeParentModel(UIBBGUIModel * NewParentModel);

		void FinalizeView();

		void FinalizeParentModel();

		UIBBTitleWidget* GetTitleViewChecked() const;

		void SetTitleViewChecked(UIBBTitleWidget* NewView);

		UIBBGUIModel* GetParentModelChecked() const;

		void SetParentModelChecked(UIBBGUIModel* NewParentModel);

	private:
		TSoftObjectPtr<UIBBTitleWidget> View;

		TSoftObjectPtr<UIBBGUIModel> ParentModel;
};