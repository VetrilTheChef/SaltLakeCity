/// SaltLakeCity 4.26

#pragma once

#include "CoreMinimal.h"
#include "GUI/Widgets/Interfaces/IBBContextRowWidget.h"
#include "GUI/Widgets/Interfaces/IBBContextWidget.h"
#include "BBContextWidget.generated.h"

/**
 * 
 */

class UIBBContextRowWidget;
class UVerticalBox;

UCLASS(Abstract, Blueprintable, BlueprintType)

class SALTLAKECITY_API UBBContextWidget : public UIBBContextWidget
{
	GENERATED_BODY()
	
	public:
		UBBContextWidget(const FObjectInitializer & ObjectInitializer);

		virtual void NativeOnInitialized() override;

		virtual void NativeOnMouseLeave(const FPointerEvent & MouseEvent) override;

		virtual EBBWidget GetType() const override;

		virtual void AddRow(UIBBContextRowWidget * & NewRowWidget) override;

		virtual void ClearRows() override;

		virtual void UpdateVisibility(UObject * NewTarget) override;

		virtual TSoftClassPtr<UIBBContextRowWidget> GetRowWidgetClass() const override;

	protected:
		UPROPERTY(EditDefaultsOnly, Category = "Classes", meta = (AllowPrivateAccess = "true"))
		TSoftClassPtr<UIBBContextRowWidget> RowWidgetClass;

		UPROPERTY(meta = (BindWidget))
		UVerticalBox * ContextBox;

		void InitializeContextBox();
};