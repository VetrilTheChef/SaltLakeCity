// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "SaltLakeCity/GUI/Controllers/Interfaces/IBBContextController.h"
#include "BBContextControllerStub.generated.h"

/**
 * 
 */

class UIBBContextRowWidget;

struct FPointerEvent;

UCLASS(NotBlueprintable)

class UBBContextControllerStub : public UIBBContextController
{
	GENERATED_BODY()

	public:
		UBBContextControllerStub();

		virtual void Initialize(UIBBContextWidget * ContextView, UIBBContextModel * ContextModel, const UIBBWidgetSpecificationFactory * WidgetSpecificationFactory, const UIBBCommandFactory * CommandFactory) override;

		virtual void Finalize() override;

		void AddRow(UIBBContextRowWidget * NewRowWidget);

		void ClearRows();

		int GetNumMouseLeaveExecutions();

		int GetNumRowClickExecutions();

	protected:
		UPROPERTY()
		UIBBContextModel * Model;

		UPROPERTY()
		UIBBContextWidget * View;

		UPROPERTY()
		TArray<UIBBContextRowWidget *> RowWidgets;

		UPROPERTY()
		int OnMouseLeaveCalls;

		UPROPERTY()
		int OnRowClickCalls;

		void InitializeModel(UIBBContextModel * ContextModel);

		void FinalizeModel();

		void InitializeView(UIBBContextWidget * ContextView);

		void FinalizeView();

		UFUNCTION()
		virtual void LeaveMouse(const FPointerEvent & MouseEvent);

		UFUNCTION()
		virtual void ClickRow();
};