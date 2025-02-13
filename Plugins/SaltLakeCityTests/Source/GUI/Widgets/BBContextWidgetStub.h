// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Widgets/Interfaces/IBBContextWidget.h"
#include "BBContextWidgetStub.generated.h"

/**
 * 
 */

class UIBBContextRowWidget;
class ULocalPlayer;

UCLASS(NotBlueprintable)

class UBBContextWidgetStub : public UIBBContextWidget
{
	GENERATED_BODY()
	
	public:
		UBBContextWidgetStub(const FObjectInitializer & ObjectInitializer);

		virtual EBBWidget GetType() const override;

		virtual void AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder) override;

		virtual void RemoveFromParent() override;

		virtual void AddRow(UIBBContextRowWidget * & NewRowWidget) override;

		virtual void ClearRows() override;

		int GetNumRows();

		UIBBContextRowWidget * GetRowWidget(int Index);

		virtual void UpdateVisibility(UObject * NewTarget) override;

		virtual TSoftClassPtr<UIBBContextRowWidget> GetRowWidgetClass() const override;

		void SetRowWidgetClass(TSoftClassPtr<UIBBContextRowWidget> NewRowWidgetClass);

		bool IsInViewport();

		void SetIsInViewport(bool IsInViewport);

		void BroadcastOnMouseLeave(FPointerEvent & MouseEvent);

	protected:
		UPROPERTY()
		TSoftClassPtr<UIBBContextRowWidget> RowWidgetClass;

		UPROPERTY()
		TArray<UIBBContextRowWidget *> RowWidgets;

		bool InViewport;
};