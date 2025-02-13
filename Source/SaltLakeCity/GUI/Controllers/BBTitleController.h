// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Controllers/Interfaces/IBBTitleController.h"
#include "BBTitleController.generated.h"

/**
 * 
 */

class UIBBCloseWidgetCommand;
class UIBBWidgetSpecification;

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBTitleController : public UIBBTitleController
{
	GENERATED_BODY()

	public:
		UBBTitleController();

		virtual void Initialize(UIBBTitleWidget * TitleView, UIBBTitleModel * TitleModel, const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, const UIBBCommandFactory * CommandFactory) override;

		virtual void Finalize() override;


	protected:
		UPROPERTY()
		UIBBTitleModel * Model;

		UPROPERTY()
		UIBBTitleWidget * View;

		UPROPERTY()
		UIBBWidgetSpecification * CloseSpecification;

		UPROPERTY()
		UIBBCloseWidgetCommand * CloseCommand;

		virtual void GetPosition(FVector2D NewPosition) override;

		virtual void GetParentWidget(UIBBWidget * & NewWidget) override;

		void InitializeModel(UIBBTitleModel * TitleModel);

		void InitializeView(UIBBTitleWidget * TitleView, UIBBTitleModel & TitleModel, const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, const UIBBCommandFactory * CommandFactory);

		void FinalizeModel();

		void FinalizeView();

		void CreateCommands(UIBBTitleWidget & TitleView, UIBBTitleModel & TitleModel, const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, const UIBBCommandFactory & CommandFactory);

		void CreateCloseCommand(UIBBTitleWidget & TitleView, UIBBTitleModel & TitleModel, const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, const UIBBCommandFactory & CommandFactory);

		void DestroyCommands();

		void DestroyCloseCommand();
};