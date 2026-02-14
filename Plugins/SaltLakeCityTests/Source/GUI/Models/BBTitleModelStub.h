// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GUI/Models/Interfaces/IBBTitleModel.h"
#include "BBTitleModelStub.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable)

class UBBTitleModelStub : public UIBBTitleModel
{
	GENERATED_BODY()

	public:
		UBBTitleModelStub();
		
		TScriptInterface<IBBWidgetTarget> GetWidgetTarget() const override;

		void SetWidgetTarget(TScriptInterface<IBBWidgetTarget> NewWidgetTarget);

		virtual UIBBWidget* GetWidget() const override;

		virtual UIBBWidgetSpecification* GetWidgetSpecification(
			const UIBBWidgetSpecificationFactory* WidgetSpecificationFactory
		) override;

		void SetWidgetSpecification(UIBBWidgetSpecification* NewWidgetSpecification);

		virtual void Initialize(UIBBTitleWidget* NewView, UIBBGUIModel* NewParentModel) override;

		virtual void Finalize() override;

		FVector2D GetPosition();

		virtual void SetPosition(FVector2D NewPosition) override;

		virtual UIBBWidget* GetParentWidget() const override;

		void SetParentWidget(UIBBWidget* NewParentWidget);

		virtual UIBBWidgetSpecification* GetParentWidgetSpecification(
			const UIBBWidgetSpecificationFactory* WidgetSpecificationFactory
		) override;

		void SetParentWidgetSpecification(UIBBWidgetSpecification* NewParentWidgetSpecification);

	protected:

		UPROPERTY()
		UIBBWidgetSpecification* WidgetSpecification;

		UPROPERTY()
		UIBBWidget* ParentWidget;

		UPROPERTY()
		TScriptInterface<IBBWidgetTarget> WidgetTarget;

		UPROPERTY()
		UIBBWidgetSpecification* ParentWidgetSpecification;

		TSoftObjectPtr<UIBBTitleWidget> View;

		TSoftObjectPtr<UIBBGUIModel> ParentModel;

		UPROPERTY()
		FVector2D Position;
};