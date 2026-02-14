// SaltLakeCity 5.7

#pragma once

#include "CoreMinimal.h"
#include "GUI/Widgets/Interfaces/IBBWidget.h"
#include "IBBSelectionWidget.generated.h"

/**
 * 
 */

UCLASS(Abstract, BlueprintType)

class SALTLAKECITY_API UIBBSelectionWidget : public UIBBWidget
{
	GENERATED_BODY()
	
	public:
		UIBBSelectionWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { };

		virtual EBBWidget GetType() const override
			PURE_VIRTUAL(UIBBSelectionWidget::GetType, return EBBWidget::None; );

		virtual void AddToScreen(int32 ZOrder = 0)
			PURE_VIRTUAL(UIBBSelectionWidget::AddToScreen, );

		virtual void SetDisplayName(FText NewDisplayName)
			PURE_VIRTUAL(UIBBSelectionWidget::SetDisplayName, );
};