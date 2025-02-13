// SaltLakeCity 4.27

#pragma once

#include "CoreMinimal.h"
#include "GUI/Controllers/Interfaces/IBBJobController.h"
#include "BBJobControllerStub.generated.h"

/**
 * 
 */

class UIBBCompositeCommand;
class UIBBCloseWidgetCommand;
class UIBBWorkComponent;

UCLASS(NotBlueprintable)

class UBBJobControllerStub : public UIBBJobController
{
	GENERATED_BODY()

	public:
		UBBJobControllerStub();

		virtual void Initialize(UIBBJobWidget * JobView, UIBBJobModel * JobModel, const UIBBWidgetFactory * WidgetFactory, const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, const UIBBCommandFactory * CommandFactory) override;

		virtual void Finalize() override;

		void SetViewCommands(UIBBCompositeCommand * NewAcceptCommand, UIBBCloseWidgetCommand * NewCancelCommand);

		UIBBWorkComponent * GetWorkComponent();

		void SetWorkComponent(UIBBWorkComponent * NewWorkComponent);

	protected:
		UPROPERTY()
		UIBBJobModel * Model;

		UPROPERTY()
		UIBBJobWidget * View;

		UPROPERTY()
		UIBBWorkComponent * WorkComponent;

		UPROPERTY()
		UIBBCompositeCommand * AcceptCommand;
		
		UPROPERTY()
		UIBBCloseWidgetCommand * CancelCommand;

		void InitializeModel(UIBBJobModel * JobModel);

		void FinalizeModel();

		void InitializeView(UIBBJobWidget * JobView);

		void FinalizeView();

		UFUNCTION()
		void UpdateConsumer();
};