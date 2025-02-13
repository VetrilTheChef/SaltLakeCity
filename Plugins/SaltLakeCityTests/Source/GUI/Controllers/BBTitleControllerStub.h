// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Controllers/Interfaces/IBBTitleController.h"
#include "BBTitleControllerStub.generated.h"

/**
 * 
 */

class UIBBCloseWidgetCommand;
class UIBBWidgetSpecification;

UCLASS(NotBlueprintable)

class UBBTitleControllerStub : public UIBBTitleController
{
	GENERATED_BODY()

	public:
		UBBTitleControllerStub();

		virtual void Initialize(UIBBTitleWidget * TitleView, UIBBTitleModel * TitleModel, const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, const UIBBCommandFactory * CommandFactory) override;

		virtual void Finalize() override;

		void SetViewCommands(UIBBCloseWidgetCommand * NewCloseCommand);

		void SetPosition(FVector2D NewPosition);

	protected:
		UPROPERTY()
		UIBBTitleModel * Model;

		UPROPERTY()
		UIBBTitleWidget * View;

		UPROPERTY()
		UIBBCloseWidgetCommand * CloseCommand;

		UPROPERTY()
		FVector2D Position;

		UPROPERTY()
		UIBBWidget * ParentWidget;

		virtual void GetPosition(FVector2D NewPosition) override;

		virtual void GetParentWidget(UIBBWidget * & NewWidget) override;
		
		void InitializeModel(UIBBTitleModel * TitleModel);

		void FinalizeModel();

		void InitializeView(UIBBTitleWidget * TitleView);

		void FinalizeView();
};