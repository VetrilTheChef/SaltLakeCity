// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GUI/Includes/BBWidgetEnum.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"
#include "IBBContextRowWidget.generated.h"

/**
 * 
 */

class UIBBCommand;
class UIBBContextRowController;
class UIBBContextWidget;
class UTexture2D;

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBContextRowWidget : public UIBBWidget
{
	GENERATED_BODY()

	public:
		UIBBContextRowWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { };

		virtual void NativeOnInitialized() override
			{ Super::NativeOnInitialized(); };

		virtual void NativeDestruct() override
			{ Super::NativeDestruct(); };

		virtual EBBWidget GetType() const
			PURE_VIRTUAL(UIBBContextRowWidget::GetType, return EBBWidget::None; );

		virtual void AddToScreen(int32 ZOrder = 0)
			PURE_VIRTUAL(UIBBContextRowWidget::AddToScreen, );

		virtual void SetRowName(FText NewName)
			PURE_VIRTUAL(UIBBContextRowWidget::SetRowName, );

		virtual void SetRowIcon(UTexture2D* NewIcon)
			PURE_VIRTUAL(UIBBContextRowWidget::SetRowIcon, );

		virtual void SetRowTooltip(FText NewTooltip)
			PURE_VIRTUAL(UIBBContextRowWidget::SetRowTooltip, );
		
		virtual void SetCommand(UIBBCommand* NewCommand)
			PURE_VIRTUAL(UIBBContextRowWidget::SetCommand, );

		DECLARE_EVENT(UIBBContextRowWidget, FBBOnClick);

		FBBOnClick& OnClicked()
			{ return OnClick; };

	protected:
		FBBOnClick OnClick;
};