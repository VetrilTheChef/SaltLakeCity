// SaltLakeCity 4.26

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

		virtual UIBBWidget * GetWidget() const override;

		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override;

		void SetWidgetSpecification(UIBBWidgetSpecification * NewWidgetSpecification);

		virtual void Initialize(UIBBTitleWidget * NewView, UIBBGUIModel * NewParentModel, AIBBHUD * NewHUD) override;

		virtual void Finalize() override;

		FVector2D GetPosition();

		virtual void SetPosition(FVector2D NewPosition) override;

		virtual UIBBWidget * GetParentWidget() const override;

		void SetParentWidget(UIBBWidget * NewParentWidget);

		virtual UIBBWidgetSpecification * GetParentWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override;

		void SetParentWidgetSpecification(UIBBWidgetSpecification * NewParentWidgetSpecification);

	protected:
		UPROPERTY()
		UIBBTitleWidget * View;

		UPROPERTY()
		UIBBWidgetSpecification * WidgetSpecification;

		UPROPERTY()
		UIBBGUIModel * ParentModel;

		UPROPERTY()
		UIBBWidget * ParentWidget;

		UPROPERTY()
		TScriptInterface<IBBWidgetTarget> WidgetTarget;

		UPROPERTY()
		UIBBWidgetSpecification * ParentWidgetSpecification;

		UPROPERTY()
		AIBBHUD * HUD;

		UPROPERTY()
		FVector2D Position;
};