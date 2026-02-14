// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"
#include "IBBContextWidget.generated.h"

/**
 * 
 */

class UIBBContextRowWidget;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBContextWidget : public UIBBWidget
{
	GENERATED_BODY()
	
	public:
		UIBBContextWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { };

		virtual void NativeOnInitialized() override
			{ Super::NativeOnInitialized(); };

		virtual void NativeOnMouseLeave(const FPointerEvent & MouseEvent) override
			{ Super::NativeOnMouseLeave(MouseEvent); };

		virtual EBBWidget GetType() const
			PURE_VIRTUAL(UIBBContextWidget::GetType, return EBBWidget::None; );

		virtual void AddToScreen(int32 ZOrder = 0)
			PURE_VIRTUAL(UIBBContextWidget::AddToScreen, );

		virtual void AddRow(UIBBContextRowWidget*& NewRowWidget)
			PURE_VIRTUAL(UIBBContextWidget::AddRow, );

		virtual void ClearRows()
			PURE_VIRTUAL(UIBBContextWidget::ClearRows, );

		virtual void UpdateVisibility(UObject* NewTarget)
			PURE_VIRTUAL(UIBBContextWidget::UpdateVisibility, );

		virtual TSoftClassPtr<UIBBContextRowWidget> GetRowWidgetClass() const
			PURE_VIRTUAL(UIBBContextWidget::GetRowWidgetClass, return TSoftClassPtr<UIBBContextRowWidget>(); );

		DECLARE_EVENT_OneParam(UIBBContextWidget, FBBMouseLeave, const FPointerEvent&);

		FBBMouseLeave& OnMouseLeave()
			{ return LeaveMouse; };

	protected:
		FBBMouseLeave LeaveMouse;
};