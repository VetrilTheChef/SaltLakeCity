// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Controllers/BBGUIController.h"
#include "Specifications/GUI/Interfaces/IBBWidgetSpecificationVisitor.h"
#include "IBBTitleController.generated.h"

/**
 * 
 */

class UIBBCommandFactory;
class UIBBTitleModel;
class UIBBTitleWidget;
class UIBBWidgetSpecificationFactory;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBTitleController : public UBBGUIController
{
	GENERATED_BODY()

	public:
		UIBBTitleController() : Super() { };

		virtual void Initialize(UIBBTitleWidget * TitleView, UIBBTitleModel * TitleModel, const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, const UIBBCommandFactory * CommandFactory) PURE_VIRTUAL(UIBBTitleController::Initialize, );

		virtual void Finalize() PURE_VIRTUAL(UIBBTitleController::Finalize, );
		
	protected:
		UFUNCTION()
		virtual void GetPosition(FVector2D NewPosition) PURE_VIRTUAL(UIBBTitleController::GetPosition, );

		UFUNCTION()
		virtual void GetParentWidget(UIBBWidget * & NewWidget) PURE_VIRTUAL(UIBBTitleController::GetParentWidget, );
};