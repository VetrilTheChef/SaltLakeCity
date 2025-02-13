// SaltLakeCity 4.25

#pragma once

#include "CoreMinimal.h"
#include "GUI/Models/Interfaces/IBBGUIModel.h"
#include "BBGUIModelStub.generated.h"

/**
 * 
 */

class UIBBWidget;
class UIBBWidgetSpecification;

UCLASS(NotBlueprintable)

class UBBGUIModelStub : public UIBBGUIModel
{
	GENERATED_BODY()

	public:
		UBBGUIModelStub();

		virtual UIBBWidget * GetWidget() const override;

		void SetWidget(UIBBWidget * NewWidget);
		
		virtual UIBBWidgetSpecification * GetWidgetSpecification(const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory) override;

		void SetWidgetSpecification(UIBBWidgetSpecification * NewWidgetSpecification);

	protected:
		UPROPERTY()
		UIBBWidget * View;

		UPROPERTY()
		UIBBWidgetSpecification * WidgetSpecification;
};