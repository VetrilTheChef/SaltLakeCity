// SaltLakeCity 4.24

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"
#include "IBBTitleWidget.generated.h"

/**
 * 
 */

class UIBBCommand;
class UIBBWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIBBTitleModel_Drag, FVector2D, NewPosition);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIBBTitleModel_DragDetect, UIBBWidget * &, NewWidget);

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBTitleWidget : public UIBBWidget
{
	GENERATED_BODY()

	public:
		UIBBTitleWidget(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer) { };

		virtual void NativeOnInitialized() override { Super::NativeOnInitialized(); };

		virtual EBBWidget GetType() const override PURE_VIRTUAL(UIBBTitleWidget::GetType, return EBBWidget::None; );

		virtual void SetCloseCommand(UIBBCommand * NewCommand) PURE_VIRTUAL(UIBBTitleWidget::SetCloseCommmand, );

		FIBBTitleModel_Drag OnDragged;

		FIBBTitleModel_DragDetect OnDragDetected;

	protected:
		virtual void NativeOnDragCancelled(const FDragDropEvent & InDragDropEvent, UDragDropOperation * InOperation) override { return Super::NativeOnDragCancelled(InDragDropEvent, InOperation); };

		virtual void NativeOnDragDetected(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent, UDragDropOperation * & OutOperation) override { return Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation); };

		virtual FReply NativeOnMouseButtonUp(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent) override { return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent); };

		virtual FReply NativeOnMouseButtonDown(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent) override { return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent); };
};