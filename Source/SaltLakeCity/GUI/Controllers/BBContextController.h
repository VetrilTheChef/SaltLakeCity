// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GUI/Includes/BBContextEnum.h"
#include "GUI/Controllers/Interfaces/IBBContextController.h"
#include "BBContextController.generated.h"

/**
 * 
 */

class UIBBContextRowWidget;

struct FPointerEvent;

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced)

class SALTLAKECITY_API UBBContextController : public UIBBContextController
{
	GENERATED_BODY()

	public:
		UBBContextController();

		virtual void Initialize(
			UIBBContextWidget* ContextView,
			UIBBContextModel* ContextModel,
			const UIBBWidgetSpecificationFactory* WidgetSpecificationFactory,
			const UIBBCommandFactory* CommandFactory
		) override;

		virtual void Finalize() override;

	protected:
		UPROPERTY()
		UIBBContextModel* Model;

		UPROPERTY()
		UIBBContextWidget* View;

		UPROPERTY()
		TMap<UIBBContextRowWidget*, EBBContext> RowWidgets;

		void InitializeModel(UIBBContextModel* ContextModel);

		void FinalizeModel();

		void InitializeView(
			UIBBContextWidget* ContextView,
			UIBBContextModel& ContextModel,
			const UIBBWidgetSpecificationFactory* WidgetSpecificationFactory,
			const UIBBCommandFactory* CommandFactory
		);

		void FinalizeView();

		void CreateRows(
			UIBBContextWidget& ContextView,
			UIBBContextModel& ContextModel,
			const UIBBWidgetSpecificationFactory* WidgetSpecificationFactory,
			const UIBBCommandFactory& CommandFactory
		);

		void DestroyRows(UIBBContextWidget& ContextView);

		UFUNCTION()
		void UpdateContext();

		UFUNCTION()
		void LeaveMouse(const FPointerEvent& MouseEvent);

		UFUNCTION()
		void ClickRow();

		void CloseView();
};